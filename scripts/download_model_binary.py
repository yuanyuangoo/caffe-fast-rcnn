#!/usr/bin/env python
import os
import sys
import time
import yaml
<<<<<<< HEAD
import hashlib
import argparse

from six.moves import urllib

=======
import urllib
import hashlib
import argparse

>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
required_keys = ['caffemodel', 'caffemodel_url', 'sha1']


def reporthook(count, block_size, total_size):
    """
    From http://blog.moleculea.com/2012/10/04/urlretrieve-progres-indicator/
    """
    global start_time
    if count == 0:
        start_time = time.time()
        return
<<<<<<< HEAD
    duration = (time.time() - start_time) or 0.01
=======
    duration = time.time() - start_time
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
    progress_size = int(count * block_size)
    speed = int(progress_size / (1024 * duration))
    percent = int(count * block_size * 100 / total_size)
    sys.stdout.write("\r...%d%%, %d MB, %d KB/s, %d seconds passed" %
                    (percent, progress_size / (1024 * 1024), speed, duration))
    sys.stdout.flush()


def parse_readme_frontmatter(dirname):
    readme_filename = os.path.join(dirname, 'readme.md')
    with open(readme_filename) as f:
        lines = [line.strip() for line in f.readlines()]
    top = lines.index('---')
<<<<<<< HEAD
    bottom = lines.index('---', top + 1)
=======
    bottom = lines[top + 1:].index('---')
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
    frontmatter = yaml.load('\n'.join(lines[top + 1:bottom]))
    assert all(key in frontmatter for key in required_keys)
    return dirname, frontmatter


def valid_dirname(dirname):
    try:
        return parse_readme_frontmatter(dirname)
    except Exception as e:
        print('ERROR: {}'.format(e))
        raise argparse.ArgumentTypeError(
            'Must be valid Caffe model directory with a correct readme.md')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Download trained model binary.')
    parser.add_argument('dirname', type=valid_dirname)
    args = parser.parse_args()

    # A tiny hack: the dirname validator also returns readme YAML frontmatter.
    dirname = args.dirname[0]
    frontmatter = args.dirname[1]
    model_filename = os.path.join(dirname, frontmatter['caffemodel'])

    # Closure-d function for checking SHA1.
    def model_checks_out(filename=model_filename, sha1=frontmatter['sha1']):
<<<<<<< HEAD
        with open(filename, 'rb') as f:
=======
        with open(filename, 'r') as f:
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
            return hashlib.sha1(f.read()).hexdigest() == sha1

    # Check if model exists.
    if os.path.exists(model_filename) and model_checks_out():
        print("Model already exists.")
        sys.exit(0)

    # Download and verify model.
<<<<<<< HEAD
    urllib.request.urlretrieve(
=======
    urllib.urlretrieve(
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
        frontmatter['caffemodel_url'], model_filename, reporthook)
    if not model_checks_out():
        print('ERROR: model did not download correctly! Run this again.')
        sys.exit(1)
