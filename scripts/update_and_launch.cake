 var allArguments = System.Environment.GetCommandLineArgs();
 var commandSplitterIndex = Array.IndexOf(allArguments, "--");
 var commands = commandSplitterIndex < 0 ? new string[0] : allArguments.Skip(commandSplitterIndex + 1).ToArray();