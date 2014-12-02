#ifndef __MUTEX_HPP__
#define __MUTEX_HPP__

struct mutex {
 private:
    uint8_t nr;
 public:
    mutex();
    void give();
    void take();
    bool take(uint32_t timeout_ms);
};

#endif /* __MUTEX_HPP__ */
