
#include "level_editor/level_editor.h"

#undef main // https://stackoverflow.com/questions/6847360/error-lnk2019-unresolved-external-symbol-main-referenced-in-function-tmainc

int main() {
    LevelEditor levelEditor;
    levelEditor.start();
    return 0;
}