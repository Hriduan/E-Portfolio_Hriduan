#!/usr/bin/env python3
"""Dependency-free checks for the generated portfolio. Runs on Termux Python."""
from html.parser import HTMLParser
from pathlib import Path
from urllib.parse import unquote, urlsplit
import re
import sys

ROOT = Path(__file__).resolve().parent.parent
class Page(HTMLParser):
    def __init__(self):
        super().__init__(convert_charrefs=True)
        self.refs = []
        self.ids = set()
        self.text = []
        self.errors = []
    def handle_starttag(self, tag, attrs):
        a = dict(attrs)
        if 'id' in a:
            if a['id'] in self.ids:
                self.errors.append('duplicate ID: ' + a['id'])
            self.ids.add(a['id'])
        for key in ('href', 'src'):
            if key in a:
                self.refs.append((tag, a[key]))
        if tag == 'img' and 'alt' not in a:
            self.errors.append('image is missing alternative text')
    def handle_data(self, data):
        self.text.append(data)

def main():
    parsed = {}
    errors = []
    files = sorted(ROOT.glob('*.html'))
    if not files:
        sys.exit('No HTML pages found. Run bash update build first.')
    for file in files:
        p = Page()
        p.feed(file.read_text(encoding='utf-8'))
        parsed[file.resolve()] = p
        errors.extend(file.name + ': ' + e for e in p.errors)
        if re.search(r',\s+(and|or|but)\b', ' '.join(p.text), re.I):
            errors.append(file.name + ': comma before and/or/but')
    for file, p in parsed.items():
        for tag, ref in p.refs:
            u = urlsplit(ref)
            if u.scheme or u.netloc:
                continue
            target = (file.parent / unquote(u.path)).resolve() if u.path else file
            if not target.is_relative_to(ROOT):
                errors.append(file.name + ': path leaves the website: ' + ref)
                continue
            if not target.exists():
                errors.append(file.name + ': missing local file: ' + ref)
            if u.fragment and target in parsed and unquote(u.fragment) not in parsed[target].ids:
                errors.append(file.name + ': missing anchor: ' + ref)
    if errors:
        print('\n'.join(errors), file=sys.stderr)
        return 1
    print(f'PASS: {len(files)} pages; local links, anchors, images and conjunction punctuation checked.')
    print('External links and FormSubmit delivery require an online check.')
    return 0
if __name__ == '__main__':
    sys.exit(main())
