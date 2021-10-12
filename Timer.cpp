#include "Timer.h"

void Timer::runTimer(std::chrono::milliseconds delay, std::function<void()> callback)
{
    currentTimerThread_ = std::thread([&, delay]
                                      {
                                          std::chrono::milliseconds counter = std::chrono::milliseconds(0);
                                          while (counter < delay && !isInterrupted_)
                                          {
                                              std::this_thread::sleep_for(updateStep_);
                                              counter += updateStep_;
                                          }

                                          if (!isInterrupted_)
                                          {
                                              callback();
                                          }
                                          else
                                          {
                                              timeRemains_ = delay - counter;
                                          }

                                          currentTimerThread_.detach();
                                      });
}

std::chrono::milliseconds Timer::stopTimer()
{
    isInterrupted_ = true;

    currentTimerThread_.join();

    isInterrupted_ = false;

    return timeRemains_;
}

bool Timer::isTimerRunning()
{
    return currentTimerThread_.joinable();
}