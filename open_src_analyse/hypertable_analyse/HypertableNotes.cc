/// Docs
Довольно много документации в заголовочных файлах


/// Error handling
// Как бросают исключение
HT_THROWF(Error::EMPTY_BLOOMFILTER, "Num elements=%lu bits_per_item=%.3f", (Lu)items_estimate, bits_per_item);

// Сереализация - передаем буффер
void serialize(StaticBuffer& buf) {
    buf.set(m_bloom_bits, m_num_bytes, false);
  }

// В доках написано, что берет во владение
/** Overloaded constructor: takes ownership of a pointer
 *
 * @param buf The pointer with data
 */
ByteString(const uint8_t *buf) : ptr(buf) { }

// именование переменных как в питоне и Goo C++ CS, and member funcs
// гугловские написания с большой буквы мне не нравятся - не естетсвенно как-то

// Интересно что это?
HT_TRY("parsing init arguments",
    properties->parse_args(argc, argv, cmdline_desc(), cmdline_hidden_descp,
                           cmdline_positional_descp, allow_unregistered));

// Common/Error.h
// добавляют довольно много инфы - строку например и имя файла
// и просто throw тоже используется

// Исключения ретранслируются - похоже при переходе между границами


// Свой foreach!
// наверное на основе boost
foreach_ht(ThreadHandleMap::value_type &val, m_thread_handle_map) {
      (val.second)->close();
    }


/// RefCounting and Pimpl
