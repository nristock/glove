Threads and Runnables
=====================

Thread
------

The ``glove::Thread`` class is basically a wrapper around std::thread adding some more functionality. A Thread can be create from a Runnable handle using ``Thread::CreateThread``. The underlying ``std::thread`` will be created and starting by invoking ``Thread::Start``.

Once the Thread's ``Runnable::Run`` exits, the executionFinished flag will be set and the system thread will terminate.

.. warning::
   The **executionFinished** flag will be set *before* the std::thread *terminates*. A call to ``Thread::Join`` may still block for a very short time.

An interrupt can be requested using ``Thread::Interrupt``. However, the runnable being run has to check the ``interruptRequested`` flag and react accordingly. If the runnable does not check the flag, ``Thread::Interrupt`` will have no effect.


Runnable
--------

A ``glove::Runnable`` is what a Thread executes. The Runnable's ``Run`` method will get a reference to the ``Thread`` executing it. ``Run`` is not required to return in a finite amount of time. However, if the Thread's interrupt flag is set, ``Run`` must terminate *"as soon as possible"*.


Example
-------

.. code-block:: cpp

   #include <glove/threading/Thread.hpp>

   using namespace glove;

   class CustomRunnable : public Runnable {
       virtual void Run(const Thread& driver) override {
           while(!driver.InterruptRequested()) {
               // do some work
           }
       }
   }

   int main() {
       auto customRunnable = std::make_shared<CustomRunnable>();
       auto customThread = Thread::CreateThread(customRunnable);

       // Start the thread
       customThread.Start();

       // do something else

       // Request the thread to exit
       customThread.Interrupt();

       // Wait for the thread to terminate
       customThread.Join();
   }
