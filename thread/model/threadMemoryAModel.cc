#include "threadMemoryAModel.h"
#include "../../console/consoleScope.h";
namespace voxlog
{
namespace thread
{
namespace model
{

using namespace voxlog::console;

namespace
{

ThreadMemoryAModel::ThreadMemoryAModel()
{
}

ThreadMemoryAModel::~ThreadMemoryAModel()
{
}
void ThreadMemoryAModel::run()
{
    test01();
}
void ThreadMemoryAModel::test01()
{
    struct
    {
        unsigned incon : 8;
        unsigned txcolor : 4;
        unsigned bgcolor : 3;
        unsigned blink : 1;
    } colorST;

    struct ByteStructA bsa{0};
    bsa.one = 1;
    bsa.two = 2;
    if (bsa.two == -2)
    {
        logger.info("   ThreadMemoryAModel::test01() equal.");
    }
    //int                k   = 32;
    //logger.numberBinary(k);
    //logger.info("   ThreadMemoryAModel::test01() call begin.");
    logger.info(bsa.one);
    logger.info(bsa.two);
    logger.numberBinary(bsa.one);
    logger.numberBinary(bsa.two);
    //logger.numberBinary(7);
    logger.info("   ThreadMemoryAModel::test01() call end.");
}

} // namespace

ThreadMemoryAModelApp::ThreadMemoryAModelApp()
{
}

ThreadMemoryAModelApp::~ThreadMemoryAModelApp()
{
}
void ThreadMemoryAModelApp::run()
{

    std::cout << "ThreadMemoryAModelApp::run() call begin." << std::endl;

    ThreadMemoryAModel model;
    model.run();

    std::cout << "ThreadMemoryAModelApp::run() call end." << std::endl;
}

} // namespace model
} // namespace thread
} // namespace voxlog