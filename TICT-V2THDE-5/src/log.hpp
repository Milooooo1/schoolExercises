#ifndef LOG_HPP_
#define LOG_HPP_

#ifdef DEBUG

#define LOG(str) \
        hwlib::cout << ((hwlib::now_us() / (60 * 1000000)) ); \
        hwlib::cout << ":"; \
        hwlib::cout << ((hwlib::now_us() / (1000000)) % 60); \
        hwlib::cout << ":"; \
        hwlib::cout << ((hwlib::now_us() / (1000)) % 1000); \
        hwlib::cout << "    "; \
        hwlib::cout << str; \
        hwlib::cout << "\n"; 

#else

#define LOG(str) 

#endif

#endif /* LOG_HPP_ */