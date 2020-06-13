#pragma once

namespace sead
{
template <typename T>
class ScopedLock
{
public:
    ScopedLock(T* lock) : mLocked(lock) { mLocked->lock(); }
    ScopedLock(const ScopedLock& other) = delete;
    const ScopedLock& operator=(const ScopedLock& other) = delete;
    virtual ~ScopedLock() { mLocked->unlock(); }

protected:
    T* mLocked;
};

template <typename T>
class ConditionalScopedLock
{
public:
    ConditionalScopedLock(T* lock, bool do_lock)
    {
        if (!do_lock)
            return;
        mLocked = lock;
        mLocked->lock();
    }
    ConditionalScopedLock(const ScopedLock& other) = delete;
    const ScopedLock& operator=(const ScopedLock& other) = delete;
    virtual ~ScopedLock()
    {
        if (mLocked)
            mLocked->unlock();
    }

protected:
    T* mLocked = nullptr;
};
}  // namespace sead
