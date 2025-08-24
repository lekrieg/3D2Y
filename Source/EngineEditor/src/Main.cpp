#include "EditorApplication.h"

int main()
{
	editor::EditorApplication editor("config.txt", "test.asset");
	editor.Run();
}
