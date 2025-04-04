// beginning a Binaryen API trace

#include "binaryen-c.h"
#include <cassert>
#include <map>
#include <math.h>
#include <stdio.h>

int main() {
  std::map<size_t, BinaryenExpressionRef> expressions;
  std::map<size_t, BinaryenFunctionRef> functions;
  std::map<size_t, RelooperBlockRef> relooperBlocks;
  BinaryenModuleRef the_module = NULL;
  RelooperRef the_relooper = NULL;
  the_module = BinaryenModuleCreate();
  expressions[size_t(NULL)] = BinaryenExpressionRef(NULL);
  {
    const char* segmentNames[] = {"0"};
    const char* segmentDatas[] = {0};
    bool segmentPassives[] = {false};
    BinaryenExpressionRef segmentOffsets[] = {0};
    BinaryenIndex segmentSizes[] = {0};
    BinaryenSetMemory(the_module,
                      256,
                      256,
                      "memory",
                      segmentNames,
                      segmentDatas,
                      segmentPassives,
                      segmentOffsets,
                      segmentSizes,
                      0,
                      0,
                      0,
                      "0");
  }
  the_relooper = RelooperCreate(the_module);
  {
    BinaryenExpressionRef children[] = {0};
    expressions[1] =
      BinaryenBlock(the_module, "bb0", children, 0, BinaryenTypeAuto());
  }
  relooperBlocks[0] = RelooperAddBlock(the_relooper, expressions[1]);
  expressions[2] = BinaryenLocalGet(the_module, 0, BinaryenTypeInt32());
  expressions[3] = BinaryenConst(the_module, BinaryenLiteralInt32(0));
  expressions[4] = BinaryenStore(the_module,
                                 4,
                                 0,
                                 0,
                                 expressions[3],
                                 expressions[2],
                                 BinaryenTypeInt32(),
                                 "0");
  expressions[5] = BinaryenReturn(the_module, expressions[0]);
  {
    BinaryenExpressionRef children[] = {expressions[4], expressions[5]};
    expressions[6] =
      BinaryenBlock(the_module, "bb1", children, 2, BinaryenTypeAuto());
  }
  relooperBlocks[1] = RelooperAddBlock(the_relooper, expressions[6]);
  RelooperAddBranch(
    relooperBlocks[0], relooperBlocks[1], expressions[0], expressions[0]);
  expressions[7] = BinaryenConst(the_module, BinaryenLiteralInt32(0));
  expressions[8] = BinaryenLoad(
    the_module, 4, 0, 0, 0, BinaryenTypeInt32(), expressions[7], "0");
  expressions[9] = BinaryenLocalSet(the_module, 0, expressions[8]);
  relooperBlocks[2] = RelooperAddBlock(the_relooper, expressions[9]);
  RelooperAddBranch(
    relooperBlocks[2], relooperBlocks[0], expressions[0], expressions[0]);
  expressions[10] =
    RelooperRenderAndDispose(the_relooper, relooperBlocks[2], 1);
  {
    BinaryenType varTypes[] = {
      BinaryenTypeInt32(), BinaryenTypeInt32(), BinaryenTypeInt64()};
    functions[0] = BinaryenAddFunction(the_module,
                                       "main",
                                       BinaryenTypeNone(),
                                       BinaryenTypeNone(),
                                       varTypes,
                                       3,
                                       expressions[10]);
  }
  BinaryenAddFunctionExport(the_module, "main", "main");
  {
    const char* segmentNames[] = {"0"};
    const char* segmentDatas[] = {0};
    bool segmentPassives[] = {false};
    BinaryenExpressionRef segmentOffsets[] = {0};
    BinaryenIndex segmentSizes[] = {0};
    BinaryenSetMemory(the_module,
                      1024,
                      1024,
                      NULL,
                      segmentNames,
                      segmentDatas,
                      segmentPassives,
                      segmentOffsets,
                      segmentSizes,
                      0,
                      0,
                      0,
                      "0");
  }
  expressions[11] = BinaryenConst(the_module, BinaryenLiteralInt32(65535));
  expressions[12] = BinaryenConst(the_module, BinaryenLiteralInt32(0));
  expressions[13] = BinaryenStore(the_module,
                                  4,
                                  0,
                                  0,
                                  expressions[12],
                                  expressions[11],
                                  BinaryenTypeInt32(),
                                  "0");
  {
    BinaryenExpressionRef operands[] = {0};
    expressions[14] =
      BinaryenCall(the_module, "main", operands, 0, BinaryenTypeNone());
  }
  {
    BinaryenExpressionRef children[] = {expressions[13], expressions[14]};
    expressions[15] =
      BinaryenBlock(the_module, NULL, children, 2, BinaryenTypeAuto());
  }
  BinaryenAddFunctionExport(the_module, "__wasm_start", "rust_entry");
  {
    BinaryenType varTypes[] = {BinaryenTypeNone()};
    functions[1] = BinaryenAddFunction(the_module,
                                       "__wasm_start",
                                       BinaryenTypeNone(),
                                       BinaryenTypeNone(),
                                       varTypes,
                                       0,
                                       expressions[15]);
  }
  assert(BinaryenModuleValidate(the_module));
  BinaryenModulePrint(the_module);
  // check that binary read-write works
  {
    char buffer[1024];
    BinaryenSetDebugInfo(1);
    size_t size = BinaryenModuleWrite(the_module, buffer, 1024);
    printf("%zd\n", size);
    BinaryenModuleRef copy = BinaryenModuleRead(buffer, size);
    BinaryenModulePrint(copy);
    BinaryenModuleDispose(copy);
  }
  BinaryenModuleDispose(the_module);
  return 0;
}
