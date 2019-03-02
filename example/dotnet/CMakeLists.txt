project(ExampleDotNet VERSION 1.0.0 LANGUAGES CSharp)

add_executable(ExampleDotNet
    App.config
    Properties/AssemblyInfo.cs
    Program.cs)

target_compile_options(ExampleDotNet PRIVATE "/langversion:6")

set_property(TARGET ExampleDotNet PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.7.1")
set_property(TARGET ExampleDotNet PROPERTY CONSOLE_EXECUTABLE TRUE)

set_property(TARGET ExampleDotNet PROPERTY VS_DOTNET_REFERENCES
    "Microsoft.CSharp"
    "System"
    "System.Linq"
    "System.Threading.Tasks"
	"OpenCLEvaluationGraphManaged")

target_link_libraries(ExampleDotNet OpenCLEvaluationGraphManaged OpenCLEvaluationGraph)