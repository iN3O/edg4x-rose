#ifndef bROwSE_H
#define bROwSE_H

#include <rose.h>
#include <Color.h>                                      // ROSE
#include <Diagnostics.h>                                // ROSE
#include <Partitioner2/Engine.h>                        // ROSE
#include <Partitioner2/Partitioner.h>                   // ROSE
#include <Wt/WApplication>
#include <Wt/WColor>

namespace bROwSE {

namespace P2 = rose::BinaryAnalysis::Partitioner2;

static const rose_addr_t NO_ADDRESS(-1);

// Convenient struct to hold settings from the command-line all in one place.
struct Settings {
    size_t deExecuteZeros;                              // threshold for removing execute permissions of zeros (zero disables)
    std::string httpAddress;                            // IP address at which to listen for HTTP connections
    unsigned short httpPort;                            // TCP port at which to listen for HTTP connections
    std::string docRoot;                                // document root directory for HTTP server
    std::string configurationName;                      // name of config file or directory containing such
    Settings()
        : deExecuteZeros(0), httpAddress("0.0.0.0"), httpPort(80), docRoot(".") {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Attributes initialized by the first construction of a Context object (where they are documented)
extern P2::Attribute::Id ATTR_NBytes;
extern P2::Attribute::Id ATTR_NInsns;
extern P2::Attribute::Id ATTR_NIntervals;
extern P2::Attribute::Id ATTR_NDiscontiguousBlocks;
extern P2::Attribute::Id ATTR_CfgGraphVizFile;
extern P2::Attribute::Id ATTR_CfgImage;
extern P2::Attribute::Id ATTR_CfgVertexCoords;
extern P2::Attribute::Id ATTR_CallGraph;
extern P2::Attribute::Id ATTR_NCallers;
extern P2::Attribute::Id ATTR_NReturns;
extern P2::Attribute::Id ATTR_MayReturn;
extern P2::Attribute::Id ATTR_StackDelta;
extern P2::Attribute::Id ATTR_Ast;
extern P2::Attribute::Id ATTR_Heat;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Context passed around to pretty much all the widgets.
class Context {
public:
    std::vector<std::string> specimenNames;             // names of specimen files
    P2::Engine engine;                                  // partitioning engine
    P2::Partitioner partitioner;                        // partitioner used by the engine
    Wt::WApplication *application;                      // Wt probably has a method to get this, but I can't find it
    
    explicit Context(const std::vector<std::string> &specimenNames, Wt::WApplication *app)
        : specimenNames(specimenNames), application(app) {
        init();
    }

private:
    void init();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      Error handling
extern Sawyer::Message::Facility mlog;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** Convert a color from ROSE's representation to Wt's representation. */
Wt::WColor toWt(const rose::Color::RGB&);


} // namespace

#endif
