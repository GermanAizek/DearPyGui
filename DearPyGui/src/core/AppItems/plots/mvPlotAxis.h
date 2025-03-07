/***************************************************************************//*/
Copyright (c) 2021 Dear PyGui, LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

/******************************************************************************/

#pragma once

#include "mvItemRegistry.h"

namespace Marvel {

    MV_REGISTER_WIDGET(mvPlotAxis, MV_ITEM_DESC_DEFAULT | MV_ITEM_DESC_CONTAINER, StorageValueTypes::None, 1);
    class mvPlotAxis : public mvAppItem
    {

    public:

        static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

        MV_APPLY_WIDGET_REGISTRATION(mvAppItemType::mvPlotAxis, add_plot_axis)
        MV_DEFAULT_CHILDREN

        MV_CREATE_CONSTANT(mvXAxis, 0);
        MV_CREATE_CONSTANT(mvYAxis, 1);

        MV_CREATE_COMMAND(reset_axis_ticks);
        MV_CREATE_COMMAND(set_axis_ticks);
        MV_CREATE_COMMAND(set_axis_limits);
        MV_CREATE_COMMAND(set_axis_limits_auto);
        MV_CREATE_COMMAND(get_axis_limits);
        MV_CREATE_COMMAND(fit_axis_data);

        MV_SET_STATES(MV_STATE_NONE);

        MV_START_PARENTS
            MV_ADD_PARENT(mvAppItemType::mvStage),
            MV_ADD_PARENT(mvAppItemType::mvTemplateRegistry),
            MV_ADD_PARENT(mvAppItemType::mvPlot)
        MV_END_PARENTS

        MV_START_COMMANDS
            MV_ADD_COMMAND(reset_axis_ticks);
            MV_ADD_COMMAND(set_axis_ticks);
            MV_ADD_COMMAND(set_axis_limits);
            MV_ADD_COMMAND(set_axis_limits_auto);
            MV_ADD_COMMAND(get_axis_limits);
            MV_ADD_COMMAND(fit_axis_data);
        MV_END_COMMANDS

        MV_START_CONSTANTS
            MV_ADD_CONSTANT(mvXAxis),
            MV_ADD_CONSTANT(mvYAxis)
        MV_END_CONSTANTS

    public:

        explicit mvPlotAxis(mvUUID uuid);

        void draw(ImDrawList* drawlist, float x, float y) override;
        void customAction(void* data = nullptr) override;
        void onChildRemoved(mvRef<mvAppItem> item) override;
        void onChildAdd(mvRef<mvAppItem> item) override;
        void handleSpecificKeywordArgs(PyObject* dict) override;
        void handleSpecificRequiredArgs(PyObject* args) override;
        void getSpecificConfiguration(PyObject* dict) override;
        void applySpecificTemplate(mvAppItem* item) override;
        void setYTicks(const std::vector<std::string>& labels, const std::vector<double>& locations);
        void resetYTicks();
        void fitAxisData();

        void setLimits(float y_min, float y_max);
        void setLimitsAuto();

        ImPlotAxisFlags getFlags() const { return _flags; }
        const ImVec2& getYLimits() const { return _limits_actual; }

    private:

        ImPlotAxisFlags          _flags = 0;
        int                      _axis = 0;
        bool                     _setLimits = false;
        ImVec2                   _limits;
        ImVec2                   _limits_actual;
        std::vector<std::string> _labels;
        std::vector<double>      _labelLocations;
        std::vector<const char*> _clabels; // to prevent conversion from string to char* every frame
        bool                     _dirty = false;

    };

}
