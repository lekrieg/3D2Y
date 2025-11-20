#include "EditorApplication.h"

#include "profiler/Profiler.h"

int main()
{
	PROFILE_FUNCTION();

	editor::EditorApplication editor("config.txt", "test.asset");

	{
		PROFILE_SCOPE("NAME test");
		int a = 0;
	}
	editor.Run();
}
