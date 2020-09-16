#! /usr/bin/python

# Copyright 2019 The ANGLE Project Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
#
# gen_overlay_widgets.py:
#  Code generation for overlay widgets.  Should be run when the widgets declaration file,
#  overlay_widgets.json, is changed.
#  NOTE: don't run this script directly. Run scripts/run_code_generation.py.

from datetime import date
import json
import sys

OUT_SOURCE_FILE_NAME = 'Overlay_autogen.cpp'
OUT_HEADER_FILE_NAME = 'Overlay_autogen.h'

IN_JSON_FILE_NAME = 'overlay_widgets.json'

OUT_SOURCE_FILE_TEMPLATE = u"""// GENERATED FILE - DO NOT EDIT.
// Generated by {script_name} using data from {input_file_name}.
//
// Copyright {copyright_year} The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// {out_file_name}:
//   Autogenerated overlay widget declarations.

#include "libANGLE/renderer/driver_utils.h"
#include "libANGLE/Overlay.h"
#include "libANGLE/OverlayWidgets.h"
#include "libANGLE/Overlay_font_autogen.h"

namespace gl
{{
using namespace overlay;

namespace
{{
int GetFontSize(int fontSize, bool largeFont)
{{
    if (largeFont && fontSize > 0)
    {{
        return fontSize - 1;
    }}
    return fontSize;
}}
}}  // anonymous namespace

void Overlay::initOverlayWidgets()
{{
    const bool kLargeFont = rx::IsAndroid();

    {init_widgets}
}}

}}  // namespace gl

"""

OUT_HEADER_FILE_TEMPLATE = u"""// GENERATED FILE - DO NOT EDIT.
// Generated by {script_name} using data from {input_file_name}.
//
// Copyright {copyright_year} The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// {out_file_name}:
//   Autogenerated overlay widget declarations.

namespace gl
{{
enum class WidgetId
{{
{widget_ids}
    InvalidEnum,
    EnumCount = InvalidEnum,
}};

// We can use this "X" macro to generate multiple code patterns.
#define ANGLE_WIDGET_ID_X(PROC) \
{widget_x_defs}

}}  // namespace gl
"""

WIDGET_INIT_TEMPLATE = u"""{{
const int32_t fontSize = GetFontSize({font_size}, kLargeFont);
const int32_t offsetX = {offset_x};
const int32_t offsetY = {offset_y};
const int32_t width = {width};
const int32_t height = {height};

widget->{subwidget}type      = WidgetType::{type};
widget->{subwidget}fontSize  = fontSize;
widget->{subwidget}coords[0] = {coord0};
widget->{subwidget}coords[1] = {coord1};
widget->{subwidget}coords[2] = {coord2};
widget->{subwidget}coords[3] = {coord3};
widget->{subwidget}color[0]  = {color_r}f;
widget->{subwidget}color[1]  = {color_g}f;
widget->{subwidget}color[2]  = {color_b}f;
widget->{subwidget}color[3]  = {color_a}f;
}}
"""

WIDGET_ID_TEMPLATE = """    // {comment}
    {name},
"""


def extract_type_and_constructor(properties):
    constructor = properties['type']
    args_separated = constructor.split('(', 1)
    if len(args_separated) == 1:
        return constructor, constructor

    type_no_constructor = args_separated[0]
    return type_no_constructor, constructor


def get_font_size_constant(properties):
    return 'kFontLayer' + properties['font'].capitalize()


def is_graph_type(type):
    return type == 'RunningGraph' or type == 'RunningHistogram'


def is_text_type(type):
    return not is_graph_type(type)


class OverlayWidget:

    def __init__(self, properties, is_graph_description=False):
        if not is_graph_description:
            self.name = properties['name']
        self.type, self.constructor = extract_type_and_constructor(properties)
        self.extract_common(properties)

        if is_graph_type(self.type):
            description_properties = properties['description']
            description_properties['type'] = 'Text'
            self.description = OverlayWidget(description_properties, True)

    def extract_common(self, properties):
        self.color = properties['color']
        self.coords = properties['coords']
        if is_graph_type(self.type):
            self.bar_width = properties['bar_width']
            self.height = properties['height']
        else:
            self.font = get_font_size_constant(properties)
            self.length = properties['length']

        self.negative_alignment = [False, False]


def is_negative_coord(coords, axis, widgets_so_far):

    if isinstance(coords[axis], unicode):
        coord_split = coords[axis].split('.')
        # The coordinate is in the form other_widget.edge.mode
        # We simply need to know if other_widget's coordinate is negative or not.
        return widgets_so_far[coord_split[0]].negative_alignment[axis]

    return coords[axis] < 0


def set_alignment_flags(overlay_widget, widgets_so_far):
    overlay_widget.negative_alignment[0] = is_negative_coord(overlay_widget.coords, 0,
                                                             widgets_so_far)
    overlay_widget.negative_alignment[1] = is_negative_coord(overlay_widget.coords, 1,
                                                             widgets_so_far)

    if is_graph_type(overlay_widget.type):
        set_alignment_flags(overlay_widget.description, widgets_so_far)


def get_offset_helper(widget, axis, smaller_coord_side):
    # Assume axis is X.  This function returns two values:
    # - An offset where the bounding box is placed at,
    # - Whether this offset is for the left or right edge.
    #
    # The input coordinate (widget.coord[axis]) is either:
    #
    # - a number: in this case, the offset is that number, and its sign determines whether this refers to the left or right edge of the bounding box.
    # - other_widget.edge.mode: this has multiple possibilities:
    #   * edge=left, mode=align: the offset is other_widget.left, the edge is left.
    #   * edge=left, mode=adjacent: the offset is other_widget.left, the edge is right.
    #   * edge=right, mode=align: the offset is other_widget.right, the edge is right.
    #   * edge=right, mode=adjacent: the offset is other_widget.right, the edge is left.
    #
    # The case for the Y axis is similar, with the edge values being top or bottom.

    coord = widget.coords[axis]
    if not isinstance(coord, unicode):
        is_left = coord >= 0
        return coord, is_left

    coord_split = coord.split('.')

    is_left = coord_split[1] == smaller_coord_side
    is_align = coord_split[2] == 'align'

    other_widget_coords = 'mState.mOverlayWidgets[WidgetId::' + coord_split[0] + ']->coords'
    other_widget_coord_index = axis + (0 if is_left else 2)
    offset = other_widget_coords + '[' + str(other_widget_coord_index) + ']'

    return offset, is_left == is_align


def get_offset_x(widget):
    return get_offset_helper(widget, 0, 'left')


def get_offset_y(widget):
    return get_offset_helper(widget, 1, 'top')


def get_bounding_box_coords(offset, width, offset_is_left, is_left_aligned):
    # See comment in generate_widget_init_helper.  This function is implementing the following:
    #
    # -  offset_is_left &&  is_left_aligned: [offset, offset + width]
    # -  offset_is_left && !is_left_aligned: [offset, std::min(offset + width, -1)]
    # - !offset_is_left &&  is_left_aligned: [std::max(1, offset - width), offset]
    # - !offset_is_left && !is_left_aligned: [offset - width, offset]

    coord_left = offset if offset_is_left else (offset + ' - ' + width)
    coord_right = (offset + ' + ' + width) if offset_is_left else offset

    if offset_is_left and not is_left_aligned:
        coord_right = 'std::min(' + coord_right + ', -1)'
    if not offset_is_left and is_left_aligned:
        coord_left = 'std::max(' + coord_left + ', 1)'

    return coord_left, coord_right


def generate_widget_init_helper(widget, is_graph_description=False):
    font_size = '0'

    # Common attributes
    color = [channel / 255.0 for channel in widget.color]
    offset_x, offset_x_is_left = get_offset_x(widget)
    offset_y, offset_y_is_top = get_offset_y(widget)

    if is_text_type(widget.type):
        # Attributes deriven from text properties
        font_size = widget.font
        width = str(widget.length) + ' * kFontGlyphWidths[fontSize]'
        height = 'kFontGlyphHeights[fontSize]'
    else:
        # Attributes deriven from graph properties
        width = str(widget.bar_width) + ' * static_cast<uint32_t>(widget->runningValues.size())'
        height = widget.height

    is_left_aligned = not widget.negative_alignment[0]
    is_top_aligned = not widget.negative_alignment[1]

    # We have offset_x, offset_y, width and height which together determine the bounding box.  If
    # offset_x_is_left, the bounding box X would be in [offset_x, offset_x + width], otherwise it
    # would be in [offset_x - width, offset_x].  Similarly for y.  Since we use negative values to
    # mean aligned to the right side of the screen, we need to make sure that:
    #
    # - if left aligned: offset_x - width is at minimum 1
    # - if right aligned: offset_x + width is at maximum -1
    #
    # We therefore have the following combinations for the X axis:
    #
    # -  offset_x_is_left &&  is_left_aligned: [offset_x, offset_x + width]
    # -  offset_x_is_left && !is_left_aligned: [offset_x, std::min(offset_x + width, -1)]
    # - !offset_x_is_left &&  is_left_aligned: [std::max(1, offset_x - width), offset_x]
    # - !offset_x_is_left && !is_left_aligned: [offset_x - width, offset_x]
    #
    # Similarly for y.
    coord0, coord2 = get_bounding_box_coords('offsetX', 'width', offset_x_is_left, is_left_aligned)
    coord1, coord3 = get_bounding_box_coords('offsetY', 'height', offset_y_is_top, is_top_aligned)

    return WIDGET_INIT_TEMPLATE.format(
        subwidget='description.' if is_graph_description else '',
        offset_x=offset_x,
        offset_y=offset_y,
        width=width,
        height=height,
        type=widget.type,
        font_size=font_size,
        coord0=coord0,
        coord1=coord1,
        coord2=coord2,
        coord3=coord3,
        color_r=color[0],
        color_g=color[1],
        color_b=color[2],
        color_a=color[3])


def generate_widget_init(widget):
    widget_init = '{\n' + widget.type + ' *widget = new ' + widget.constructor + ';\n'

    widget_init += generate_widget_init_helper(widget)
    widget_init += 'mState.mOverlayWidgets[WidgetId::' + widget.name + '].reset(widget);\n'

    if is_graph_type(widget.type):
        widget_init += generate_widget_init_helper(widget.description, True)

    widget_init += '}\n'

    return widget_init


def main():
    if len(sys.argv) == 2 and sys.argv[1] == 'inputs':
        print(IN_JSON_FILE_NAME)
        return
    if len(sys.argv) == 2 and sys.argv[1] == 'outputs':
        outputs = [
            OUT_SOURCE_FILE_NAME,
            OUT_HEADER_FILE_NAME,
        ]
        print(','.join(outputs))
        return

    with open(IN_JSON_FILE_NAME) as fin:
        layout = json.loads(fin.read())

    widgets = layout['widgets']

    # Read the layouts from the json file and determine alignment of widgets (as they can refer to
    # other widgets.
    overlay_widgets = {}
    for widget_properties in widgets:
        widget = OverlayWidget(widget_properties)
        overlay_widgets[widget.name] = widget
        set_alignment_flags(widget, overlay_widgets)

    # Go over the widgets again and generate initialization code.  Note that we need to iterate over
    # the widgets in order, so we can't use the overlay_widgets dictionary for iteration.
    init_widgets = []
    for widget_properties in widgets:
        init_widgets.append(generate_widget_init(overlay_widgets[widget_properties['name']]))

    with open(OUT_SOURCE_FILE_NAME, 'w') as outfile:
        outfile.write(
            OUT_SOURCE_FILE_TEMPLATE.format(
                script_name=__file__,
                copyright_year=date.today().year,
                input_file_name=IN_JSON_FILE_NAME,
                out_file_name=OUT_SOURCE_FILE_NAME,
                init_widgets='\n'.join(init_widgets)))
        outfile.close()

    with open(OUT_HEADER_FILE_NAME, 'w') as outfile:
        widget_ids = [WIDGET_ID_TEMPLATE.format(**widget) for widget in widgets]
        widget_x_defs = ["PROC(" + widget['name'] + ")" for widget in widgets]

        outfile.write(
            OUT_HEADER_FILE_TEMPLATE.format(
                script_name=__file__,
                copyright_year=date.today().year,
                input_file_name=IN_JSON_FILE_NAME,
                out_file_name=OUT_SOURCE_FILE_NAME,
                widget_ids=''.join(widget_ids),
                widget_x_defs=' \\\n'.join(widget_x_defs)))
        outfile.close()


if __name__ == '__main__':
    sys.exit(main())
