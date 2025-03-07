
def deprecated(reason):

	string_types = (type(b''), type(u''))

	if isinstance(reason, string_types):

		def decorator(func1):

			fmt1 = "Call to deprecated function {name} ({reason})."

			@functools.wraps(func1)
			def new_func1(*args, **kwargs):
				warnings.simplefilter('always', DeprecationWarning)
				warnings.warn(
					fmt1.format(name=func1.__name__, reason=reason),
					category=DeprecationWarning,
					stacklevel=2
				)
				warnings.simplefilter('default', DeprecationWarning)
				return func1(*args, **kwargs)

			return new_func1

		return decorator

	elif inspect.isfunction(reason):

		func2 = reason
		fmt2 = "Call to deprecated function {name}."

		@functools.wraps(func2)
		def new_func2(*args, **kwargs):
			warnings.simplefilter('always', DeprecationWarning)
			warnings.warn(
				fmt2.format(name=func2.__name__),
				category=DeprecationWarning,
				stacklevel=2
			)
			warnings.simplefilter('default', DeprecationWarning)
			return func2(*args, **kwargs)

		return new_func2

@deprecated("Use 'configure_app(docking=True, docking_space=dock_space)'.")
def enable_docking(dock_space: bool = False) -> None:
    internal_dpg.configure_app(docking=True, docking_space=dock_space)

@deprecated("Use 'get_app_configuration()['version']'.")
def get_dearpygui_version() -> str:
    return internal_dpg.get_app_configuration()["version"]

@deprecated("Use 'configure_app(init_file=file)'.")
def set_init_file(file: str = "dpg.ini") -> None:
    internal_dpg.configure_app(init_file=file)

@deprecated("Use 'configure_app(init_file=file, load_init_file=True)'.")
def load_init_file(file: str) -> None:
    internal_dpg.configure_app(init_file=file, load_init_file=True)

@deprecated("Use: `is_viewport_ok(...)`")
def is_viewport_created() -> bool:
    return internal_dpg.is_viewport_ok()

@deprecated("Use: \ncreate_viewport()\nsetup_dearpygui()\nshow_viewport()")
def setup_viewport():
    internal_dpg.create_viewport()
    internal_dpg.setup_dearpygui()
    internal_dpg.show_viewport()

@deprecated("Use: `bind_item_theme(...)`")
def set_item_theme(item : Union[int, str], theme : Union[int, str]) -> None:
	return internal_dpg.bind_item_theme(item, theme)

@deprecated("Use: `bind_item_type_disabled_theme(...)`")
def set_item_type_disabled_theme(item : int, theme : Union[int, str]) -> None:
	return internal_dpg.bind_item_type_disabled_theme(item, theme)

@deprecated("Use: `bind_item_type_theme(...)`")
def set_item_type_theme(item : int, theme : Union[int, str]) -> None:
	return internal_dpg.bind_item_type_theme(item, theme)

@deprecated("Use: `bind_item_font(...)`")
def set_item_font(item : Union[int, str], font : Union[int, str]) -> None:
	return internal_dpg.bind_item_font(item, font)

@deprecated("Use: `add_item_activated_handler(...)`")
def add_activated_handler(parent : Union[int, str], *, label: str =None, user_data: Any =None, use_internal_label: bool =True, tag: Union[int, str] =0, callback: Callable =None, show: bool =True) -> Union[int, str]:
	return internal_dpg.add_item_activated_handler(parent, label=label, user_data=user_data, use_internal_label=use_internal_label, tag=tag, callback=callback, show=show)

@deprecated("Use: `add_item_active_handler(...)`")
def add_active_handler(parent : Union[int, str], *, label: str =None, user_data: Any =None, use_internal_label: bool =True, tag: Union[int, str] =0, callback: Callable =None, show: bool =True) -> Union[int, str]:
	return internal_dpg.add_item_active_handler(parent, label=label, user_data=user_data, use_internal_label=use_internal_label, tag=tag, callback=callback, show=show)

@deprecated("Use: `add_item_clicked_handler(...)`")
def add_clicked_handler(parent : Union[int, str], button : int =-1, *, label: str =None, user_data: Any =None, use_internal_label: bool =True, tag: Union[int, str] =0, callback: Callable =None, show: bool =True) -> Union[int, str]:
	return internal_dpg.add_item_clicked_handler(parent, button, label=label, user_data=user_data, use_internal_label=use_internal_label, tag=tag, callback=callback, show=show)

@deprecated("Use: `add_item_deactived_after_edit_handler(...)`")
def add_deactivated_after_edit_handler(parent : Union[int, str], *, label: str =None, user_data: Any =None, use_internal_label: bool =True, tag: Union[int, str] =0, callback: Callable =None, show: bool =True) -> Union[int, str]:
	return internal_dpg.add_item_deactivated_after_edit_handler(parent, label=label, user_data=user_data, use_internal_label=use_internal_label, tag=tag, callback=callback, show=show)

@deprecated("Use: `add_item_deactivated_handler(...)`")
def add_deactivated_handler(parent : Union[int, str], *, label: str =None, user_data: Any =None, use_internal_label: bool =True, tag: Union[int, str] =0, callback: Callable =None, show: bool =True) -> Union[int, str]:
	return internal_dpg.add_item_deactivated_handler(parent, label=label, user_data=user_data, use_internal_label=use_internal_label, tag=tag, callback=callback, show=show)

@deprecated("Use: `add_item_edited_handler(...)`")
def add_edited_handler(parent : Union[int, str], *, label: str =None, user_data: Any =None, use_internal_label: bool =True, tag: Union[int, str] =0, callback: Callable =None, show: bool =True) -> Union[int, str]:
	return internal_dpg.add_item_edited_handler(parent, label=label, user_data=user_data, use_internal_label=use_internal_label, tag=tag, callback=callback, show=show)

@deprecated("Use: `add_item_focus_handler(...)`")
def add_focus_handler(parent : Union[int, str], *, label: str =None, user_data: Any =None, use_internal_label: bool =True, tag: Union[int, str] =0, callback: Callable =None, show: bool =True) -> Union[int, str]:
	return internal_dpg.add_item_focus_handler(parent, label=label, user_data=user_data, use_internal_label=use_internal_label, tag=tag, callback=callback, show=show)

@deprecated("Use: `add_item_hover_handler(...)`")
def add_hover_handler(parent : Union[int, str], *, label: str =None, user_data: Any =None, use_internal_label: bool =True, tag: Union[int, str] =0, callback: Callable =None, show: bool =True) -> Union[int, str]:
	return internal_dpg.add_item_hover_handler(parent, label=label, user_data=user_data, use_internal_label=use_internal_label, tag=tag, callback=callback, show=show)

@deprecated("Use: `add_item_resize_handler(...)`")
def add_resize_handler(parent : Union[int, str], *, label: str =None, user_data: Any =None, use_internal_label: bool =True, tag: Union[int, str] =0, callback: Callable =None, show: bool =True) -> Union[int, str]:
	return internal_dpg.add_item_resize_handler(parent, label=label, user_data=user_data, use_internal_label=use_internal_label, tag=tag, callback=callback, show=show)

@deprecated("Use: `add_item_toggled_open_handler(...)`")
def add_toggled_open_handler(parent : Union[int, str], *, label: str =None, user_data: Any =None, use_internal_label: bool =True, tag: Union[int, str] =0, callback: Callable =None, show: bool =True) -> Union[int, str]:
	return internal_dpg.add_item_toggled_open_handler(parent, label=label, user_data=user_data, use_internal_label=use_internal_label, tag=tag, callback=callback, show=show)

@deprecated("Use: `add_item_visible_handler(...)`")
def add_visible_handler(parent : Union[int, str], *, label: str =None, user_data: Any =None, use_internal_label: bool =True, tag: Union[int, str] =0, callback: Callable =None, show: bool =True) -> Union[int, str]:
	return internal_dpg.add_item_visible_handler(parent, label=label, user_data=user_data, use_internal_label=use_internal_label, tag=tag, callback=callback, show=show)

@deprecated("Use: `bind_colormap(...)`")
def set_colormap(item : Union[int, str], source : Union[int, str]) -> None:
	return internal_dpg.bind_colormap(item, source)

@deprecated("Use: `bind_theme(0)`")
def reset_default_theme(item : Union[int, str], source : Union[int, str]) -> None:
	return internal_dpg.bind_theme(item, source)

@deprecated
def set_staging_mode(mode : bool) -> None:
	pass

@deprecated
def add_table_next_column(*, label: str =None, user_data: Any =None, use_internal_label: bool =True, id: Union[int, str] =0, parent: Union[int, str] =0, before: Union[int, str] =0, show: bool =True) -> Union[int, str]:
	pass

@deprecated("Use: add_stage")
def add_staging_container(*, label: str =None, user_data: Any =None, use_internal_label: bool =True, id: Union[int, str] =0) -> Union[int, str]:
	return internal_dpg.add_stage(label=label, user_data=user_data, use_internal_label=use_internal_label, id=id)

@deprecated("Use: stage")
@contextmanager
def staging_container(*, label: str =None, user_data: Any =None, use_internal_label: bool =True, id: Union[int, str] =0) -> Union[int, str]:
	"""
	Undocumented function
	Args:
		**label (str): Overrides 'name' as label.
		**user_data (Any): User data for callbacks.
		**use_internal_label (bool): Use generated internal label instead of user specified (appends ### uuid).
		**id (Union[int, str]): Unique id used to programmatically refer to the item.If label is unused this will be the label.
	Yields:
		Union[int, str]
	"""
	try:
		warnings.warn("'staging_container' is deprecated and was changed to 'stage'", DeprecationWarning, 2)
		widget = internal_dpg.add_stage_container(label=label, user_data=user_data, use_internal_label=use_internal_label, id=id)
		internal_dpg.push_container_stack(widget)
		yield widget
	finally:
		internal_dpg.pop_container_stack()

@deprecated("Use: add_spacer(...)")
def add_spacing(*, label: str =None, user_data: Any =None, use_internal_label: bool =True, tag: Union[int, str] =0, indent: int =-1,
                parent: Union[int, str] =0, before: Union[int, str] =0, show: bool =True, pos: Union[List[int], Tuple[int]] =[], count: int =1) -> Union[int, str]:
	"""	Adds vertical spacing.

	Args:
		label (str, optional): Overrides 'name' as label.
		user_data (Any, optional): User data for callbacks.
		use_internal_label (bool, optional): Use generated internal label instead of user specified (appends ### uuid).
		tag (Union[int, str], optional): Unique id used to programmatically refer to the item.If label is unused this will be the label.
		indent (int, optional): Offsets the widget to the right the specified number multiplied by the indent style.
		parent (Union[int, str], optional): Parent to add this item to. (runtime adding)
		before (Union[int, str], optional): This item will be displayed before the specified item in the parent.
		show (bool, optional): Attempt to render widget.
		pos (Union[List[int], Tuple[int]], optional): Places the item relative to window coordinates, [0,0] is top left.
		count (int, optional): Number of spacings to add the size is dependant on the curret style.
	Returns:
		Union[int, str]
	"""

	with internal_dpg.group(tag=tag) as result_id:
		for i in range(count):
			internal_dpg.add_spacer(label=label, user_data=user_data, use_internal_label=use_internal_label, tag=tag, indent=indent, parent=parent, before=before, show=show, pos=pos, count=count)
	return result_id

@deprecated("Use: add_spacer(...)")
def add_dummy(*, label: str =None, user_data: Any =None, use_internal_label: bool =True, tag: Union[int, str] =0, width: int =0, height: int =0, indent: int =-1, parent: Union[int, str] =0, before: Union[int, str] =0, show: bool =True, pos: Union[List[int], Tuple[int]] =[]) -> Union[int, str]:
	"""	Adds a spacer or 'dummy' object.

	Args:
		label (str, optional): Overrides 'name' as label.
		user_data (Any, optional): User data for callbacks.
		use_internal_label (bool, optional): Use generated internal label instead of user specified (appends ### uuid).
		tag (Union[int, str], optional): Unique id used to programmatically refer to the item.If label is unused this will be the label.
		width (int, optional): Width of the item.
		height (int, optional): Height of the item.
		indent (int, optional): Offsets the widget to the right the specified number multiplied by the indent style.
		parent (Union[int, str], optional): Parent to add this item to. (runtime adding)
		before (Union[int, str], optional): This item will be displayed before the specified item in the parent.
		show (bool, optional): Attempt to render widget.
		pos (Union[List[int], Tuple[int]], optional): Places the item relative to window coordinates, [0,0] is top left.
	Returns:
		Union[int, str]
	"""

	return internal_dpg.add_spacer(label=label, user_data=user_data, use_internal_label=use_internal_label, tag=tag, width=width, height=height, indent=indent, parent=parent, before=before, show=show, pos=pos)

@deprecated("Use: `destroy_context()`")
def cleanup_dearpygui() -> None:
	return internal_dpg.destroy_context()


@deprecated("Use: `add_child_window()`")
def add_child(*, label: str =None, user_data: Any =None, use_internal_label: bool =True, tag: Union[int, str] =0, width: int =0, height: int =0, indent: int =-1, parent: Union[int, str] =0, before: Union[int, str] =0, payload_type: str ='$$DPG_PAYLOAD', drop_callback: Callable =None, show: bool =True, pos: Union[List[int], Tuple[int]] =[], filter_key: str ='', delay_search: bool =False, tracked: bool =False, track_offset: float =0.5, border: bool =True, autosize_x: bool =False, autosize_y: bool =False, no_scrollbar: bool =False, horizontal_scrollbar: bool =False, menubar: bool =False) -> Union[int, str]:
	"""	Adds an embedded child window. Will show scrollbars when items do not fit.

	Args:
		label (str, optional): Overrides 'name' as label.
		user_data (Any, optional): User data for callbacks
		use_internal_label (bool, optional): Use generated internal label instead of user specified (appends ### uuid).
		tag (Union[int, str], optional): Unique id used to programmatically refer to the item.If label is unused this will be the label.
		width (int, optional): Width of the item.
		height (int, optional): Height of the item.
		indent (int, optional): Offsets the widget to the right the specified number multiplied by the indent style.
		parent (Union[int, str], optional): Parent to add this item to. (runtime adding)
		before (Union[int, str], optional): This item will be displayed before the specified item in the parent.
		payload_type (str, optional): Sender string type must be the same as the target for the target to run the payload_callback.
		drop_callback (Callable, optional): Registers a drop callback for drag and drop.
		show (bool, optional): Attempt to render widget.
		pos (Union[List[int], Tuple[int]], optional): Places the item relative to window coordinates, [0,0] is top left.
		filter_key (str, optional): Used by filter widget.
		delay_search (bool, optional): Delays searching container for specified items until the end of the app. Possible optimization when a container has many children that are not accessed often.
		tracked (bool, optional): Scroll tracking
		track_offset (float, optional): 0.0f:top, 0.5f:center, 1.0f:bottom
		border (bool, optional): Shows/Hides the border around the sides.
		autosize_x (bool, optional): Autosize the window to fit it's items in the x.
		autosize_y (bool, optional): Autosize the window to fit it's items in the y.
		no_scrollbar (bool, optional):  Disable scrollbars (window can still scroll with mouse or programmatically).
		horizontal_scrollbar (bool, optional): Allow horizontal scrollbar to appear (off by default).
		menubar (bool, optional): Shows/Hides the menubar at the top.
	Returns:
		Union[int, str]
	"""

	return internal_dpg.add_child_window(label=label, user_data=user_data, use_internal_label=use_internal_label, tag=tag, width=width, height=height, indent=indent, parent=parent, before=before, payload_type=payload_type, drop_callback=drop_callback, show=show, pos=pos, filter_key=filter_key, delay_search=delay_search, tracked=tracked, track_offset=track_offset, border=border, autosize_x=autosize_x, autosize_y=autosize_y, no_scrollbar=no_scrollbar, horizontal_scrollbar=horizontal_scrollbar, menubar=menubar)


@deprecated("Use: `child_window()`")
@contextmanager
def child(*, label: str =None, user_data: Any =None, use_internal_label: bool =True, tag: Union[int, str] =0, width: int =0, height: int =0, indent: int =-1, parent: Union[int, str] =0, before: Union[int, str] =0, payload_type: str ='$$DPG_PAYLOAD', drop_callback: Callable =None, show: bool =True, pos: Union[List[int], Tuple[int]] =[], filter_key: str ='', delay_search: bool =False, tracked: bool =False, track_offset: float =0.5, border: bool =True, autosize_x: bool =False, autosize_y: bool =False, no_scrollbar: bool =False, horizontal_scrollbar: bool =False, menubar: bool =False) -> Union[int, str]:
	"""	Adds an embedded child window. Will show scrollbars when items do not fit.

	Args:
		label (str, optional): Overrides 'name' as label.
		user_data (Any, optional): User data for callbacks
		use_internal_label (bool, optional): Use generated internal label instead of user specified (appends ### uuid).
		tag (Union[int, str], optional): Unique id used to programmatically refer to the item.If label is unused this will be the label.
		width (int, optional): Width of the item.
		height (int, optional): Height of the item.
		indent (int, optional): Offsets the widget to the right the specified number multiplied by the indent style.
		parent (Union[int, str], optional): Parent to add this item to. (runtime adding)
		before (Union[int, str], optional): This item will be displayed before the specified item in the parent.
		payload_type (str, optional): Sender string type must be the same as the target for the target to run the payload_callback.
		drop_callback (Callable, optional): Registers a drop callback for drag and drop.
		show (bool, optional): Attempt to render widget.
		pos (Union[List[int], Tuple[int]], optional): Places the item relative to window coordinates, [0,0] is top left.
		filter_key (str, optional): Used by filter widget.
		delay_search (bool, optional): Delays searching container for specified items until the end of the app. Possible optimization when a container has many children that are not accessed often.
		tracked (bool, optional): Scroll tracking
		track_offset (float, optional): 0.0f:top, 0.5f:center, 1.0f:bottom
		border (bool, optional): Shows/Hides the border around the sides.
		autosize_x (bool, optional): Autosize the window to fit it's items in the x.
		autosize_y (bool, optional): Autosize the window to fit it's items in the y.
		no_scrollbar (bool, optional):  Disable scrollbars (window can still scroll with mouse or programmatically).
		horizontal_scrollbar (bool, optional): Allow horizontal scrollbar to appear (off by default).
		menubar (bool, optional): Shows/Hides the menubar at the top.
	Yields:
		Union[int, str]
	"""
	try:
		widget = internal_dpg.add_child_window(label=label, user_data=user_data, use_internal_label=use_internal_label, tag=tag, width=width, height=height, indent=indent, parent=parent, before=before, payload_type=payload_type, drop_callback=drop_callback, show=show, pos=pos, filter_key=filter_key, delay_search=delay_search, tracked=tracked, track_offset=track_offset, border=border, autosize_x=autosize_x, autosize_y=autosize_y, no_scrollbar=no_scrollbar, horizontal_scrollbar=horizontal_scrollbar, menubar=menubar)
		internal_dpg.push_container_stack(widget)
		yield widget
	finally:
		internal_dpg.pop_container_stack()

