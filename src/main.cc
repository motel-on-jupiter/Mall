/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "core/MallMain.h"
#include "mojgame/catalogue/log_emitter/DebuggerConsoleLogEmitter.h"
#include "mojgame/catalogue/log_emitter/FileLogEmitter.h"
#include "mojgame/includer/crtdbg_include.h"
#include "mojgame/logging/Logger.h"

#define kDebugAlloc (-1)

int main(int argc, char **argv) {
#ifdef _MSC_VER
#ifdef _DEBUG
  // Validate the detection for memory leak
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  _CrtSetBreakAlloc(kDebugAlloc);
#endif
#endif

  // Set up logger
  mojgame::LOGGER().PushEmitter(mojgame::DEBUGGER_CONSOLE_LOG_EMITTER());
  mojgame::LOGGER().PushEmitter(mojgame::STDERR_LOG_EMITTER());

  // Load the configuration on the external file
  if (argc != 2) {
    mojgame::LOGGER().Error("Usage: %s <configfile>", argv[0]);
    return -1;
  }

  // Start the main function for BeFuture
  return MallMain(argc, argv, argv[1]);
}
