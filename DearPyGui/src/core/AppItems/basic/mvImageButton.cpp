#include "mvImageButton.h"
#include "mvContext.h"
#include "mvItemRegistry.h"
#include "mvPythonExceptions.h"
#include "AppItems/fonts/mvFont.h"
#include "AppItems/themes/mvTheme.h"
#include "AppItems/containers/mvDragPayload.h"

namespace Marvel {

	void mvImageButton::InsertParser(std::map<std::string, mvPythonParser>* parsers)
	{
		std::vector<mvPythonDataElement> args;

		AddCommonArgs(args,(CommonParserArgs)(
			MV_PARSER_ARG_ID |
			MV_PARSER_ARG_WIDTH |
			MV_PARSER_ARG_HEIGHT |
			MV_PARSER_ARG_INDENT |
			MV_PARSER_ARG_PARENT |
			MV_PARSER_ARG_BEFORE |
			MV_PARSER_ARG_SOURCE |
			MV_PARSER_ARG_CALLBACK |
			MV_PARSER_ARG_SHOW |
			MV_PARSER_ARG_ENABLED |
			MV_PARSER_ARG_FILTER |
			MV_PARSER_ARG_DROP_CALLBACK |
			MV_PARSER_ARG_DRAG_CALLBACK |
			MV_PARSER_ARG_PAYLOAD_TYPE |
			MV_PARSER_ARG_TRACKED |
			MV_PARSER_ARG_POS)
		);

		args.push_back({ mvPyDataType::UUID, "texture_id" });
		args.push_back({ mvPyDataType::Integer, "frame_padding", mvArgType::KEYWORD_ARG, "-1" });
		args.push_back({ mvPyDataType::FloatList, "tint_color", mvArgType::KEYWORD_ARG, "(255, 255, 255, 255)", "Applies a color tint to the entire texture." });
		args.push_back({ mvPyDataType::FloatList, "background_color", mvArgType::KEYWORD_ARG, "(0, 0, 0, 0)", "Displays a border of the specified color around the texture." });
		args.push_back({ mvPyDataType::FloatList, "uv_min", mvArgType::KEYWORD_ARG, "(0.0, 0.0)", "Normalized texture coordinates min point."});
		args.push_back({ mvPyDataType::FloatList, "uv_max", mvArgType::KEYWORD_ARG, "(1.0, 1.0)", "Normalized texture coordinates max point."});

		mvPythonParserSetup setup;
		setup.about = "Adds an button with a texture. uv_min and uv_max represent the normalized texture coordinates of the original image that will be shown. Using range (0.0,0.0)->(1.0,1.0) texture coordinates will generally display the entire texture";
		setup.category = { "Widgets", "Textures" };
		setup.returnType = mvPyDataType::UUID;

		mvPythonParser parser = FinalizeParser(setup, args);

		parsers->insert({ s_command, parser });
	}

	mvImageButton::mvImageButton(mvUUID uuid)
		: mvAppItem(uuid)
	{
	}

	void mvImageButton::applySpecificTemplate(mvAppItem* item)
	{
		auto titem = static_cast<mvImageButton*>(item);
		_textureUUID = titem->_textureUUID;
		_uv_min = titem->_uv_min;
		_uv_max = titem->_uv_max;
		_tintColor = titem->_tintColor;
		_backgroundColor = titem->_backgroundColor;
		_texture = titem->_texture;
		_internalTexture = titem->_internalTexture;
		_framePadding = titem->_framePadding;
	}

	void mvImageButton::draw(ImDrawList* drawlist, float x, float y)
	{

		//-----------------------------------------------------------------------------
		// pre draw
		//-----------------------------------------------------------------------------

		// show/hide
		if (!_show)
			return;

		// focusing
		if (_focusNextFrame)
		{
			ImGui::SetKeyboardFocusHere();
			_focusNextFrame = false;
		}

		// cache old cursor position
		ImVec2 previousCursorPos = ImGui::GetCursorPos();

		// set cursor position if user set
		if (_dirtyPos)
			ImGui::SetCursorPos(_state.pos);

		// update widget's position state
		_state.pos = { ImGui::GetCursorPosX(), ImGui::GetCursorPosY() };

		// set item width
		if (_width != 0)
			ImGui::SetNextItemWidth((float)_width);

		// set indent
		if (_indent > 0.0f)
			ImGui::Indent(_indent);

		// push font if a font object is attached
		if (_font)
		{
			ImFont* fontptr = static_cast<mvFont*>(_font.get())->getFontPtr();
			ImGui::PushFont(fontptr);
		}

		// themes
		if (auto classTheme = getClassThemeComponent())
			static_cast<mvThemeComponent*>(classTheme.get())->draw(nullptr, 0.0f, 0.0f);

		if (_theme)
		{
			static_cast<mvTheme*>(_theme.get())->setSpecificEnabled(_enabled);
			static_cast<mvTheme*>(_theme.get())->setSpecificType((int)getType());
			static_cast<mvTheme*>(_theme.get())->draw(nullptr, 0.0f, 0.0f);
		}

		//-----------------------------------------------------------------------------
		// draw
		//-----------------------------------------------------------------------------
		{

			if (_texture)
			{

				if (_internalTexture)
					_texture->draw(drawlist, x, y);

				if (!_texture->_state.ok)
					return;

				// if width/height is not set by user, use texture dimensions
				if (_width == 0)
					_width = _texture->_width;

				if (_height == 0)
					_height = _texture->_height;

				void* texture = nullptr;

				if (_texture->getType() == mvAppItemType::mvStaticTexture)
					texture = static_cast<mvStaticTexture*>(_texture.get())->getRawTexture();
				else if (_texture->getType() == mvAppItemType::mvRawTexture)
					texture = static_cast<mvRawTexture*>(_texture.get())->getRawTexture();
				else
					texture = static_cast<mvDynamicTexture*>(_texture.get())->getRawTexture();

				ImGui::PushID(_uuid);
				if (ImGui::ImageButton(texture, ImVec2((float)_width, (float)_height),
					ImVec2(_uv_min.x, _uv_min.y), ImVec2(_uv_max.x, _uv_max.y), _framePadding,
					_backgroundColor, _tintColor))
				{
					if(_alias.empty())
						GContext->callbackRegistry->addCallback(getCallback(false), _uuid, nullptr, _user_data);
					else
						GContext->callbackRegistry->addCallback(getCallback(false), _alias, nullptr, _user_data);
				}
				ImGui::PopID();
			}
		}

		//-----------------------------------------------------------------------------
		// update state
		//-----------------------------------------------------------------------------
		UpdateAppItemState(_state);

		//-----------------------------------------------------------------------------
		// post draw
		//-----------------------------------------------------------------------------

		// set cursor position to cached position
		if (_dirtyPos)
			ImGui::SetCursorPos(previousCursorPos);

		if (_indent > 0.0f)
			ImGui::Unindent(_indent);

		// pop font off stack
		if (_font)
			ImGui::PopFont();

		// handle popping themes
		if (auto classTheme = getClassThemeComponent())
			static_cast<mvThemeComponent*>(classTheme.get())->customAction();

		if (_theme)
		{
			static_cast<mvTheme*>(_theme.get())->setSpecificEnabled(_enabled);
			static_cast<mvTheme*>(_theme.get())->setSpecificType((int)getType());
			static_cast<mvTheme*>(_theme.get())->customAction();
		}

		if (_handlerRegistry)
			_handlerRegistry->customAction(&_state);

		// handle drag & drop payloads
		for (auto& item : _children[3])
			item->draw(nullptr, ImGui::GetCursorPosX(), ImGui::GetCursorPosY());

		// handle drag & drop if used
		if (_dropCallback)
		{
			ScopedID id(_uuid);
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(_payloadType.c_str()))
				{
					auto payloadActual = static_cast<const mvDragPayload*>(payload->Data);

					if (_alias.empty())
						GContext->callbackRegistry->addCallback(_dropCallback,_uuid, payloadActual->getDragData(), nullptr);
					else
						GContext->callbackRegistry->addCallback(_dropCallback,_alias, payloadActual->getDragData(), nullptr);
				}

				ImGui::EndDragDropTarget();
			}
		}
	}

	void mvImageButton::handleSpecificRequiredArgs(PyObject* dict)
	{
		if (!VerifyRequiredArguments(GetParsers()[s_command], dict))
			return;

		for (int i = 0; i < PyTuple_Size(dict); i++)
		{
			PyObject* item = PyTuple_GetItem(dict, i);
			switch (i)
			{
			case 0:
			{
				_textureUUID = GetIDFromPyObject(item);
				_texture = GetRefItem(*GContext->itemRegistry, _textureUUID);
				if (_texture)
					break;
				else if (_textureUUID == MV_ATLAS_UUID)
				{
					_texture = std::make_shared<mvStaticTexture>(_textureUUID);
					_internalTexture = true;
					break;
				}
				else
				{
					mvThrowPythonError(mvErrorCode::mvTextureNotFound, s_command, "Texture not found.", this);
					break;
				}
			}

			default:
				break;
			}
		}

		
	}

	void mvImageButton::handleSpecificKeywordArgs(PyObject* dict)
	{
		if (dict == nullptr)
			return;

		if (PyObject* item = PyDict_GetItemString(dict, "uv_min")) _uv_min = ToVec2(item);
		if (PyObject* item = PyDict_GetItemString(dict, "uv_max")) _uv_max = ToVec2(item);
		if (PyObject* item = PyDict_GetItemString(dict, "tint_color")) _tintColor = ToColor(item);
		if (PyObject* item = PyDict_GetItemString(dict, "background_color")) _backgroundColor = ToColor(item);
		if (PyObject* item = PyDict_GetItemString(dict, "frame_padding")) _framePadding = ToInt(item);
        if (PyObject* item = PyDict_GetItemString(dict, "texture_id"))
        {
            _textureUUID = GetIDFromPyObject(item);
            _texture = GetRefItem(*GContext->itemRegistry, _textureUUID);
            if (_textureUUID == MV_ATLAS_UUID)
            {
                _texture = std::make_shared<mvStaticTexture>(_textureUUID);
                _internalTexture = true;
            }
            else if(_texture)
            {
                _internalTexture = false;
            }
            else
            {
                mvThrowPythonError(mvErrorCode::mvTextureNotFound, s_command, "Texture not found.", this);
			}
        }
	}

	void mvImageButton::getSpecificConfiguration(PyObject* dict)
	{
		if (dict == nullptr)
			return;

		PyDict_SetItemString(dict, "uv_min", mvPyObject(ToPyPair(_uv_min.x, _uv_min.y)));
		PyDict_SetItemString(dict, "uv_max", mvPyObject(ToPyPair(_uv_max.x, _uv_max.y)));
		PyDict_SetItemString(dict, "tint_color", mvPyObject(ToPyColor(_tintColor)));
		PyDict_SetItemString(dict, "background_color", mvPyObject(ToPyColor(_backgroundColor)));
		PyDict_SetItemString(dict, "frame_padding", mvPyObject(ToPyInt(_framePadding)));
		PyDict_SetItemString(dict, "texture_id", mvPyObject(ToPyUUID(_textureUUID)));
	}

}
