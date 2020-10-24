# Copyright 2020 The ANGLE Project Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
"""ANGLE implementation of //build/skia_gold_common/skia_gold_properties.py."""

import subprocess
from skia_gold_common import skia_gold_properties


class ANGLESkiaGoldProperties(skia_gold_properties.SkiaGoldProperties):

    @staticmethod
    def _GetGitOriginMasterHeadSha1():
        try:
            return subprocess.check_output(['git', 'rev-parse', 'origin/master'],
                                           shell=_IsWin(),
                                           cwd=ANGLE_SRC_DIR).strip()
        except subprocess.CalledProcessError:
            return None


def _IsWin():
    return sys.platform == 'win32'
