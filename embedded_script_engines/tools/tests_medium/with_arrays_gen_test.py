# coding: utf-8
from generators_cpp_code import maker_sources

if __name__ == '__main__':
    header_to_wrap = 'idata/sampler.h'
    maker_sources.make_complect(header_to_wrap)


