#ifndef __MUTEX_HPP__
#define __MUTEX_HPP__

struct mutex {
 private:
    uint8_t nr;
 public:
    mutex();
    void give();
    void take();
    void take(uint32_t timeout);
};

#endif /* __MUTEX_HPP__ */
