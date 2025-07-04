set_project("Hexis")
set_version("0.0.1")

add_rules("mode.debug", "mode.release")

option("shared",   { description = "Build as shared library",     default = false })
option("unittest", { description = "Build unittest (xmake test)", default = false })

option("math", { description = "Enables the math module", default = false})

set_languages("c++23")

if is_mode("debug") then
	set_warnings("allextra", "error")
end

if has_config("unittest") then 
	add_requires("doctest")
end

target("HXCore")
    add_defines("HX_CORE_BUILD")

    if has_config("shared") then
        set_kind("shared")
        add_defines("HX_CORE_SHARED")
    else
        set_kind("static")
    end

    add_includedirs("include/", { public = true })
    add_headerfiles("include/(Hexis/Core/*.h)", "include/(Hexis/Core/*.inl)")
    add_headerfiles("include/(Hexis/Core/**/*.h)", "include/(Hexis/Core/**/*.inl)")

    add_files("src/Core/*.cpp")
    add_files("src/Core/**/*.cpp")

    if (has_config("unittest")) then 
        for _, file in ipairs(os.files("test/Core/test_*.cpp")) do
            add_tests(path.basename(file), {
                kind = "binary",
                files = file,
                languages = "c++23",
                packages = "doctest",
                defines = "DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN"
            })
        end
    end

if has_config("math") then
    target("HXMath")
        add_defines("HX_MATH_BUILD")

        if has_config("shared") then
            set_kind("shared")
            add_defines("HX_MATH_SHARED")
        else
            set_kind("static")
        end

        add_deps("HXCore")

        add_includedirs("include/", { public = true })
        add_headerfiles("include/(Hexis/Math/*.h)", "include/(Hexis/Math/*.inl)")
        --add_headerfiles("include/(Hexis/Core/**/*.h)")

        add_files("src/Math/*.cpp")
        add_files("src/Math/**/*.cpp")

        if (has_config("unittest")) then 
            for _, file in ipairs(os.files("test/Math/test_*.cpp")) do
                add_tests(path.basename(file), {
                    kind = "binary",
                    files = file,
                    languages = "c++23",
                    packages = "doctest",
                    defines = "DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN"
                })
            end
        end
end