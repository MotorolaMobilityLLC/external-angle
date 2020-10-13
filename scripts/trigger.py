#!/usr/bin/python2
#
# Copyright 2019 The ANGLE Project Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
#
# trigger.py:
#   Helper script for triggering GPU tests on swarming.

import argparse
import hashlib
import logging
import os
import re
import subprocess
import sys


def parse_args():
    parser = argparse.ArgumentParser(os.path.basename(sys.argv[0]))
    parser.add_argument('gn_path', help='path to GN. (e.g. out/Release)')
    parser.add_argument('test', help='test name. (e.g. angle_end2end_tests)')
    parser.add_argument('os_dim', help='OS dimension. (e.g. Windows-10)')
    parser.add_argument('-s', '--shards', default=1, help='number of shards', type=int)
    parser.add_argument('-p', '--pool', default='Chrome-GPU', help='swarming pool')
    parser.add_argument('-g', '--gpu', help='GPU dimension. (e.g. intel-hd-630-win10-stable)')
    parser.add_argument('-t', '--device-type', help='Android device type (e.g. bullhead)')
    parser.add_argument('-o', '--device-os', help='Android OS.')

    return parser.parse_known_args()


def main():
    args, unknown = parse_args()
    path = args.gn_path.replace('\\', '/')
    out_gn_path = '//' + path
    out_file_path = os.path.join(*path.split('/'))

    # Attempt to detect standalone vs chromium component build.
    is_standalone = not os.path.isdir(os.path.join('third_party', 'angle'))

    mb_script_path = os.path.join('tools', 'mb', 'mb.py')
    mb_args = ['python', mb_script_path, 'isolate', out_gn_path, args.test]

    if is_standalone:
        logging.info('Standalone mode detected.')
        mb_args += ['-i', os.path.join('infra', 'gn_isolate_map.pyl')]

    if subprocess.call(mb_args):
        sys.exit('MB step failed, exiting')

    isolate_cmd_path = os.path.join('tools', 'luci-go', 'isolate')
    isolate_file = os.path.join(out_file_path, '%s.isolate' % args.test)
    isolated_file = os.path.join(out_file_path, '%s.isolated' % args.test)

    isolate_args = [
        isolate_cmd_path, 'archive', '-I', 'https://isolateserver.appspot.com', '-i', isolate_file,
        '-s', isolated_file
    ]
    subprocess.check_call(isolate_args)
    with open(isolated_file, 'rb') as f:
        sha = hashlib.sha1(f.read()).hexdigest()

    logging.info('Got an isolated SHA of %s' % sha)
    swarming_script_path = os.path.join('tools', 'luci-go', 'swarming')

    swarming_args = [
        swarming_script_path, 'trigger', '-S', 'chromium-swarm.appspot.com', '-I',
        'https://isolateserver.appspot.com', '-d', 'os=' + args.os_dim, '-d', 'pool=' + args.pool,
        '-s', sha
    ]

    # Define a user tag.
    try:
        whoami = subprocess.check_output(['whoami'])
        # Strip extra stuff (e.g. on Windows we are 'hostname\username')
        whoami = re.sub(r'\w+[^\w]', '', whoami.strip())
        swarming_args += ['-user', whoami]
    except:
        pass

    if args.gpu:
        swarming_args += ['-d', 'gpu=' + args.gpu]

    if args.device_type:
        swarming_args += ['-d', 'device_type=' + args.device_type]

    if args.device_os:
        swarming_args += ['-d', 'device_os=' + args.device_os]

    if args.shards > 1:
        for i in range(args.shards):
            shard_args = swarming_args[:]
            shard_args.extend([
                '--env',
                'GTEST_TOTAL_SHARDS=%d' % args.shards,
                '--env',
                'GTEST_SHARD_INDEX=%d' % i,
            ])
            if unknown:
                shard_args += ["--"] + unknown

            logging.info(' '.join(shard_args))
            subprocess.call(shard_args)
    else:
        if unknown:
            swarming_args += ["--"] + unknown
        subprocess.call(swarming_args)
    return 0


if __name__ == '__main__':
    sys.exit(main())
