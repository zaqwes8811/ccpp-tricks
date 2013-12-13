# coding: utf-8

# std
from os.path import basename
import os

# Other
from generator.cpp import utils

# App
from generators_cpp_code.v8_api_gen import vectors
import utils_local
from generators_cpp_code import maker_sources

if __name__ == '__main__':
    def main():
        header_to_wrap = 'idata/sampler.h'
        class_transmit_code = utils.ReadFile(header_to_wrap)
        declarations, class_name = maker_sources.get_declarations_from_header(class_transmit_code)

        # Names
        dir = os.path.dirname(header_to_wrap)
        header_name = basename(header_to_wrap)
        header_no_ext = header_name.split(os.extsep)[0]

        # Targets
        pair_name = os.sep.join((dir, 'v8_'+header_no_ext))
        builder = vectors.BuilderArrayWrapper(declarations)
        code = maker_sources.make_header_file(pair_name, class_name, builder, header_name)
        utils_local.write_source(pair_name+'.h', code)

        # source
        code = maker_sources.make_source_file(builder)
        utils_local.write_source(pair_name+'.cc', code)

    main()


