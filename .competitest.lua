return {
    save_current_file = true,
    testcases_directory = "../testcases",
    template_file = {
        cpp = "template.cpp",
    },
    evaluate_template_modifiers = false,
    received_files_extension = "cpp",
    received_problems_path = "$(CWD)/problems/$(PROBLEM).$(FEXT)",
    received_problems_prompt_path = false,
    received_contests_directory = "$(CWD)/problems",
    received_contests_problems_path = "$(PROBLEM).$(FEXT)",
    received_contests_prompt_directory = false,
    received_contests_prompt_extension = false,
    open_received_problems = true,
    open_received_contests = true,
    compile_command = {
        cpp = {
            exec = "g++",
            args = {
                "-std=c++17",
                "-O2",
                "-Wall",
                "-Wextra",
                "-Wshadow",
                "-DLOCAL",
                "-Wl,--stack,268435456",
                "$(FNAME)",
                "-o",
                "../build/$(FNOEXT).exe",
            },
        },
    },
    run_command = {
        cpp = {
            exec = "../build/$(FNOEXT).exe",
        },
    },
}
