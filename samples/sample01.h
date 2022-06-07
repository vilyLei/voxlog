#pragma once
#include "../thread/model/threadModel01.h"
#include "../thread/model/threadModel02.h"
#include "../thread/model/conditionVariableModel.h"
#include "../thread/model/futureModel.h"
#include "../thread/model/promiseModel.h"
#include "../thread/model/TaskServerModel.h"
#include "../thread/model/timeModel.h"
#include "../io/file/SimpleFile.h"
#include "../core/algorithm/sortAlgorithm.h"
#include "../samples/templ/resultofBase.h"
#include "../thread/model/threadMemoryAModel.h"
#include "../thread/model/atomicAModel.h"

namespace voxlog
{
namespace samples
{
using namespace voxlog::thread::model;
using namespace voxlog::io::file;
using namespace voxlog::core::algorithm;

namespace
{

void atomicTest01()
{

    using moduleType = AtomicAModelApp;
    moduleType model{};
    model.run();
}
void memoryTest01()
{

    using moduleType = ThreadMemoryAModelApp;
    moduleType model{};
    model.run();

}
void templateTest01()
{
    using namespace voxlog::samples::templ;
    resultofTestMain();
}
void algorithmTest01()
{

    using moduleType = SortAlgorthmApp;
    moduleType model{};
    model.run();
}
void timeTest01()
{
    using moduleType = TimeModelApp;
    moduleType model{};
    model.run();
}
void fileTest01()
{
    SimpleFile file;
    file.test();
}
void serverTest()
{
    using moduleType = TaskServerAppModel;
    moduleType model{};
    model.run();
}
void baseTest03()
{

    using moduleType = FutureThreadModel;
    //using moduleType = PromiseThreadModelApp;
    moduleType model{};
    model.run();
}
void baseTest02()
{

    using moduleType = ConditionVariableThreadModel;
    moduleType model{};
    model.run();
}
void baseTest01()
{

    using threadModelType = SharedMemoryAndMutexLockThreadModel;
    //using threadModelType = SeparatedMemoryAndMutexLockThreadModel;

    threadModelType model{};
    model.run();
}
} // namespace
void testMain01()
{
    //timeTest01();
    //serverTest();
    //baseTest01();
    //baseTest02();
    //baseTest03();
    //fileTest01();
    //algorithmTest01();
    //memoryTest01();
    atomicTest01();

    //templateTest01();
}
} // namespace samples
} // namespace voxlog