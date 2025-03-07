First Steps
===========

.. meta::
   :description lang=en: The starting point for the tutorial set.

Tutorials will give a broad overview and working knowledge of DPG. Tutorials do not cover every detail
so refer to the documentation on each topic to learn more.

Installing
-----------

Python 3.6 (64 bit) or above is required.

.. code-block::

    pip install dearpygui

First Run
---------

Confirm the pip install by runing the code block below.

**Code:**

.. code-block:: python

    import dearpygui.dearpygui as dpg

    dpg.create_context()
    dpg.create_viewport(title='Custom Title', width=600, height=200)

    with dpg.window(label="Example Window"):
        dpg.add_text("Hello, world")
        dpg.add_button(label="Save")
        dpg.add_input_text(label="string", default_value="Quick brown fox")
        dpg.add_slider_float(label="float", default_value=0.273, max_value=1)

    dpg.setup_dearpygui()
    dpg.show_viewport()
    dpg.start_dearpygui()
    dpg.destroy_context()

**Result:**

.. image:: https://raw.githubusercontent.com/hoffstadt/DearPyGui/assets/BasicUsageExample1.PNG

.. note:: 
    The main script must always:

    - Create the context :py:func:`create_context <dearpygui.dearpygui.create_context>`
    - Create the viewport :py:func:`create_viewport <dearpygui.dearpygui.create_viewport>`
    - Setup dearpygui :py:func:`show_viewport <dearpygui.dearpygui.show_viewport>`
    - Show the viewport :py:func:`show_viewport <dearpygui.dearpygui.show_viewport>`
    - Start dearpygui :py:func:`start_dearpygui <dearpygui.dearpygui.start_dearpygui>`
    - Clean up the context :py:func:`destroy_context <dearpygui.dearpygui.destroy_context>`
