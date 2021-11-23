#!/usr/bin/env python
# Copyright 2021 The ANGLE Project Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
"""Script to generate the test spec JSON files. Calls Chromium's generate_buildbot_json.

=== NOTE: DO NOT RUN THIS SCRIPT DIRECTLY. ===
Run scripts/run_code_generation.py instead to update necessary hashes.

"""

import os
import pprint
import sys
import subprocess

d = os.path.dirname
THIS_DIR = d(os.path.abspath(__file__))
TESTING_BBOT_DIR = os.path.join(d(d(THIS_DIR)), 'testing', 'buildbot')
sys.path.insert(0, TESTING_BBOT_DIR)

import generate_buildbot_json

# Add custom mixins here.
ADDITIONAL_MIXINS = {
    'angle_skia_gold_test': {
        '$mixin_append': {
            'args': [
                '--git-revision=${got_angle_revision}',
                # BREAK GLASS IN CASE OF EMERGENCY
                # Uncommenting this argument will bypass all interactions with Skia
                # Gold in any tests that use it. This is meant as a temporary
                # emergency stop in case of a Gold outage that's affecting the bots.
                # '--bypass-skia-gold-functionality',
            ],
            'precommit_args': [
                '--gerrit-issue=${patch_issue}',
                '--gerrit-patchset=${patch_set}',
                '--buildbucket-id=${buildbucket_build_id}',
            ],
        }
    },

    # TODO(jmadill): De-duplicate when landed in Chrome. http://crbug.com/1236818
    'angle_linux_nvidia_gtx_1660_stable': {
        'swarming': {
            'dimensions': {
                'gpu': '10de:2184-440.100',
                'os': 'Ubuntu-18.04.5|Ubuntu-18.04.6',
                'pool': 'chromium.tests.gpu',
            },
        },
    },
    'angle_win10_nvidia_gtx_1660_stable': {
        'swarming': {
            'dimensions': {
                'gpu': '10de:2184-27.21.14.5638',
                'os': 'Windows-10-18363',
                'pool': 'chromium.tests.gpu',
            },
        },
    },
}

MIXIN_FILE_NAME = os.path.join(THIS_DIR, 'mixins.pyl')
MIXINS_PYL_TEMPLATE = """\
# GENERATED FILE - DO NOT EDIT.
# Generated by {script_name} using data from {data_source}
#
# Copyright 2021 The ANGLE Project Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
#
# This is a .pyl, or "Python Literal", file. You can treat it just like a
# .json file, with the following exceptions:
# * all keys must be quoted (use single quotes, please);
# * comments are allowed, using '#' syntax; and
# * trailing commas are allowed.
#
# For more info see Chromium's mixins.pyl in testing/buildbot.

{mixin_data}
"""


def main():
    if len(sys.argv) > 1:
        gen_bb_json = os.path.join(TESTING_BBOT_DIR, 'generate_buildbot_json.py')
        mixins_pyl = os.path.join(TESTING_BBOT_DIR, 'mixins.pyl')
        inputs = [
            'test_suite_exceptions.pyl', 'test_suites.pyl', 'variants.pyl', 'waterfalls.pyl',
            gen_bb_json, mixins_pyl
        ]
        outputs = ['angle.json', 'mixins.pyl']
        if sys.argv[1] == 'inputs':
            print(','.join(inputs))
        elif sys.argv[1] == 'outputs':
            print(','.join(outputs))
        else:
            print('Invalid script parameters')
            return 1
        return 0

    chromium_args = generate_buildbot_json.BBJSONGenerator.parse_args(sys.argv[1:])
    chromium_generator = generate_buildbot_json.BBJSONGenerator(chromium_args)
    chromium_generator.load_configuration_files()

    override_args = sys.argv[1:] + ['--pyl-files-dir', THIS_DIR]
    angle_args = generate_buildbot_json.BBJSONGenerator.parse_args(override_args)
    angle_generator = generate_buildbot_json.BBJSONGenerator(angle_args)
    angle_generator.load_configuration_files()
    angle_generator.resolve_configuration_files()

    seen_mixins = set()
    for waterfall in angle_generator.waterfalls:
        seen_mixins = seen_mixins.union(waterfall.get('mixins', set()))
        for bot_name, tester in waterfall['machines'].iteritems():
            seen_mixins = seen_mixins.union(tester.get('mixins', set()))
    for suite in angle_generator.test_suites.values():
        if isinstance(suite, list):
            # Don't care about this, it's a composition, which shouldn't include a
            # swarming mixin.
            continue
        for test in suite.values():
            assert isinstance(test, dict)
            seen_mixins = seen_mixins.union(test.get('mixins', set()))

    found_mixins = ADDITIONAL_MIXINS.copy()
    for mixin in seen_mixins:
        if mixin in found_mixins:
            continue
        assert (mixin in chromium_generator.mixins)
        found_mixins[mixin] = chromium_generator.mixins[mixin]

    pp = pprint.PrettyPrinter(indent=2)

    format_data = {
        'script_name': os.path.basename(__file__),
        'data_source': 'waterfall.pyl and Chromium\'s mixins.pyl',
        'mixin_data': pp.pformat(found_mixins),
    }
    generated_mixin_pyl = MIXINS_PYL_TEMPLATE.format(**format_data)

    with open(MIXIN_FILE_NAME, 'w') as f:
        f.write(generated_mixin_pyl)
        f.close()

    return angle_generator.main()


if __name__ == '__main__':  # pragma: no cover
    sys.exit(main())
