# coding: utf-8

# Std
import unittest

#
from generators_cpp_code import maker_sources


class TestExtractorVarsDeclarations(unittest.TestCase):
    def test_shuffle(self):
        header_to_wrap = 'source_forge/up2D.h'
        maker_sources.make_complect(header_to_wrap)
