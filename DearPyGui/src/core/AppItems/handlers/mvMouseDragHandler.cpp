#include "mvMouseDragHandler.h"
#include "mvLog.h"
#include "mvItemRegistry.h"
#include "mvPythonExceptions.h"
#include "mvUtilities.h"

namespace Marvel {

	void mvMouseDragHandler::InsertParser(std::map<std::string, mvPythonParser>* parsers)
	{
		std::vector<mvPythonDataElement> args;

		AddCommonArgs(args,(CommonParserArgs)(
			MV_PARSER_ARG_ID |
			MV_PARSER_ARG_CALLBACK |
			MV_PARSER_ARG_SHOW)
		);

		args.push_back({ mvPyDataType::Integer, "button", mvArgType::POSITIONAL_ARG, "-1", "Submits callback for all mouse buttons" });
		args.push_back({ mvPyDataType::Float, "threshold", mvArgType::POSITIONAL_ARG, "10.0", "The threshold the mouse must be dragged before the callback is ran" });
		args.push_back({ mvPyDataType::UUID, "parent", mvArgType::KEYWORD_ARG, "internal_dpg.mvReservedUUID_1", "Parent to add this item to. (runtime adding)" });
		
		mvPythonParserSetup setup;
		setup.about = "Adds a mouse drag handler.";
		setup.category = { "Events", "Widgets" };
		setup.returnType = mvPyDataType::UUID;
		
		mvPythonParser parser = FinalizeParser(setup, args);

		parsers->insert({ s_command, parser });
	}

	mvMouseDragHandler::mvMouseDragHandler(mvUUID uuid)
		:
		mvAppItem(uuid)
	{

	}

	void mvMouseDragHandler::applySpecificTemplate(mvAppItem* item)
	{
		auto titem = static_cast<mvMouseDragHandler*>(item);
		_button = titem->_button;
		_threshold = titem->_threshold;
	}

	void mvMouseDragHandler::draw(ImDrawList* drawlist, float x, float y)
	{
		if (_button == -1)
		{
			for (int i = 0; i < IM_ARRAYSIZE(ImGui::GetIO().MouseDown); i++)
			{
				if (ImGui::IsMouseReleased(i))
					ImGui::ResetMouseDragDelta(i);

				if (ImGui::IsMouseDragging(i, _threshold))
				{
					GContext->callbackRegistry->submitCallback([=]()
						{
							if (_alias.empty())
								GContext->callbackRegistry->runCallback(getCallback(false), _uuid,
									ToPyMTrip(i, ImGui::GetMouseDragDelta(i).x, ImGui::GetMouseDragDelta(i).y), _user_data);
							else
								GContext->callbackRegistry->runCallback(getCallback(false), _alias,
									ToPyMTrip(i, ImGui::GetMouseDragDelta(i).x, ImGui::GetMouseDragDelta(i).y), _user_data);
						});
				}
			}
		}

		else if (ImGui::IsMouseDragging(_button, _threshold))
		{
			if (ImGui::IsMouseReleased(_button))
				ImGui::ResetMouseDragDelta(_button);
			GContext->callbackRegistry->submitCallback([=]()
				{
					if (_alias.empty())
						GContext->callbackRegistry->runCallback(getCallback(false), _uuid,
							ToPyMTrip(_button, ImGui::GetMouseDragDelta(_button).x, ImGui::GetMouseDragDelta(_button).y), _user_data);
					else
						GContext->callbackRegistry->runCallback(getCallback(false), _alias,
							ToPyMTrip(_button, ImGui::GetMouseDragDelta(_button).x, ImGui::GetMouseDragDelta(_button).y), _user_data);
				});
		}
	}

	void mvMouseDragHandler::handleSpecificPositionalArgs(PyObject* dict)
	{
		if (!VerifyPositionalArguments(GetParsers()[s_command], dict))
			return;

		for (int i = 0; i < PyTuple_Size(dict); i++)
		{
			PyObject* item = PyTuple_GetItem(dict, i);
			switch (i)
			{
			case 0:
				_button = ToInt(item);
				break;
			case 1:
				_threshold = ToFloat(item);
				break;

			default:
				break;
			}
		}
	}

	void mvMouseDragHandler::handleSpecificKeywordArgs(PyObject* dict)
	{
		if (dict == nullptr)
			return;

		if (PyObject* item = PyDict_GetItemString(dict, "button")) _button = ToInt(item);
		if (PyObject* item = PyDict_GetItemString(dict, "threshold")) _threshold = ToFloat(item);
	}

	void mvMouseDragHandler::getSpecificConfiguration(PyObject* dict)
	{
		if (dict == nullptr)
			return;

		PyDict_SetItemString(dict, "button", mvPyObject(ToPyInt(_button)));
		PyDict_SetItemString(dict, "threshold", mvPyObject(ToPyFloat(_threshold)));
	}
}