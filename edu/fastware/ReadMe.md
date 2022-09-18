
Chandler Capur:
- llvm
  CppCon 2017: Chandler Carruth “Going Nowhere Faster”
  CppCon 2015: Chandler Carruth "Tuning C++: Benchmarks, and CPUs, and Compilers! Oh My!"

Perf help:
```shell

cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..

perf_4.9 stat ./projects/high_perf/hp_benchmark

perf_4.9 record -g ./projects/high_perf/hp_benchmark

perf_4.9 report -g 'graph,0.5,caller'

cat /proc/sys/kernel/perf_event_paranoid
sudo sh -c 'echo -1 >/proc/sys/kernel/perf_event_paranoid'
sudo sh -c 'echo 0 > /proc/sys/kernel/kptr_restrict'

Note: shorter code took more time in benchmark

```


################################################################

Alexandrescu:
- [code::dive conference 2015 - Andrei Alexandrescu - Writing Fast Code I](https://www.youtube.com/watch?v=vrfYLlR8X8k&ab_channel=NOKIATechnologyCenterWroc%C5%82aw)


Yuri Minaev:
- [Hypercritical C++ Code Review - Yuri Minaev  C++ on Sea](https://www.youtube.com/watch?v=f1_Iwh33f9I&ab_channel=cpponsea)

Jason Turner:
- [CppCon 2016: Jason Turner “Practical Performance Practices"](https://www.youtube.com/watch?v=uzF4u9KgUWI&t=78s&ab_channel=CppCon)

Alan Talbot:
- [CppCon 2018: Alan Talbot “Moving Faster: Everyday efficiency in modern C++”](https://www.youtube.com/watch?v=EovBkh9wDnM&t=1751s&ab_channel=CppCon)

Ben Deane:
- [CppCon 2019: Ben Deane “Everyday Efficiency: In-Place Construction (Back to Basics?)”](https://www.youtube.com/watch?v=oTMSgI1XjF8&t=14s&ab_channel=CppCon)

