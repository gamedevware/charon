//////////////////////////////////////////////////////////////////////
// ARGUMENTS
//////////////////////////////////////////////////////////////////////

var allArguments = System.Environment.GetCommandLineArgs();
var commandSplitterIndex = Array.IndexOf(allArguments, "--");
var commands = commandSplitterIndex < 0 ? new string[0] : allArguments.Skip(commandSplitterIndex + 1).ToArray();
 
var target = Argument("target", "Default");
var outputDirectory = Directory(System.IO.Path.GetFullPath(Argument("outputDirectory", "./")));

var charonToolPath = (outputDirectory + File("./GameDevWare.Charon/tools/Charon.exe")).Path;
var charonSearchDirectoryPath = (outputDirectory + Directory("GameDevWare.Charon/tools/")).Path;

var nugetFeedUrl = "https://api.nuget.org/v3/index.json";

//////////////////////////////////////////////////////////////////////
// PREPARATION
//////////////////////////////////////////////////////////////////////

Setup(context =>
{
	if (!DirectoryExists(outputDirectory))
	{
		Information($"Creating directory '{outputDirectory}'.");
		CreateDirectory(outputDirectory);
	}
});

Teardown(context =>
{

});

//////////////////////////////////////////////////////////////////////
// TASKS
//////////////////////////////////////////////////////////////////////


Task("Install-Charon-Package")
	.Does(context =>
{
	NuGetInstall("GameDevWare.Charon", new NuGetInstallSettings {
		ExcludeVersion  = true,
		ArgumentCustomization = args => args.Append("-PackageSaveMode nupkg"),
		NonInteractive = true,
		Prerelease = true,
		RequireConsent = false,
		Source = new[] { nugetFeedUrl },
		OutputDirectory = outputDirectory,
		Verbosity = NuGetVerbosity.Quiet
	});
});

Task("Locate-Charon-Executable")
	.WithCriteria(!FileExists(charonToolPath))
	.IsDependentOn("Install-Charon-Package")
	.Does(context =>
{
	Information($"Locating 'Charon.exe' in '{charonSearchDirectoryPath}'.");
	
	var files = GetFiles(charonSearchDirectoryPath.FullPath + "**/Charon.exe");
	foreach(var file in files)
	{
		Information($"Executable 'Charon.exe' found at '{file}'.");
		charonToolPath = file;
	}
	
	if (!FileExists(charonToolPath)) {
		throw new Exception($"Unable to locate 'Charon.exe' in '{charonSearchDirectoryPath}'.");
	}
});

Task("Run-Charon-Executable-Server-Start")
	.WithCriteria(commands.Length == 0)
	.IsDependentOn("Locate-Charon-Executable")
	.Does(context =>
{
	var exitCodeWithArgument =	StartProcess
	(
		charonToolPath.FullPath,
		new ProcessSettings {
			Arguments = new ProcessArgumentBuilder().Append("HELP"),
		}
	);

	// This should output 0 as valid arguments supplied
	Information("Exit code: {0}", exitCodeWithArgument);
});

Task("Run-Charon-Executable-With-Command")
	.WithCriteria(commands.Length > 0)
	.IsDependentOn("Locate-Charon-Executable")
	.Does(context =>
{
	var exitCodeWithArgument =	StartProcess
	(
		charonToolPath.FullPath,
		new ProcessSettings {
			Arguments = ProcessArgumentBuilder.FromStrings(commands),
		}
	);

	// This should output 0 as valid arguments supplied
	Information("Exit code: {0}", exitCodeWithArgument);
});

//////////////////////////////////////////////////////////////////////
// TASK TARGETS
//////////////////////////////////////////////////////////////////////

Task("Default")
	.IsDependentOn("Run-Charon-Executable-Server-Start")
	.IsDependentOn("Run-Charon-Executable-With-Command");

//////////////////////////////////////////////////////////////////////
// EXECUTION
//////////////////////////////////////////////////////////////////////

RunTarget(target);