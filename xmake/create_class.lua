-- defined at the end of the file
local headerTemplate, sourceTemplate

task("create-class")

set_menu({
	-- Settings menu usage
	usage = "xmake create-class [options] name",
	description = "Helper for class creation",
	options =
	{
		-- Set k mode as key-only bool parameter
		{nil, "nocpp", "k", nil, "Set this if you don't want a .cpp to be created (header-only classes)" },
		{nil, "name", "v", nil, "Class name" }
	}
})

on_run(function ()
	import("core.base.option")

	local classPath = option.get("name")
	if not classPath then
		os.raise("missing class name")
	end

	local className = path.basename(classPath)

	local files = {
		{ TargetPath = path.join("include", "SerializationLib", classPath) .. ".h", Template = headerTemplate },
	}

	if not option.get("nocpp") then
		table.insert(files, { TargetPath = path.join("src", "SerializationLib", classPath) .. ".cpp", Template = sourceTemplate })
	end

	local replacements = {
		CLASS_NAME = className,
		CLASS_PATH = classPath,
	}

	for _, file in pairs(files) do
		local content = file.Template:gsub("%%([%u_]+)%%", function (kw)
			local r = replacements[kw]
			if not r then
				os.raise("missing replacement for " .. kw)
			end

			return r
		end)

		io.writefile(file.TargetPath, content)
	end
end)

headerTemplate = [[
#pragma once
#include "SerializationLibrary.h"

namespace Serialization
{
	class SERIAL_API %CLASS_NAME%
	{
		public:
			%CLASS_NAME%() = default;
			%CLASS_NAME%(const %CLASS_NAME%&) = delete;
			%CLASS_NAME%(%CLASS_NAME%&&) = delete;
			~%CLASS_NAME%() = default;

			%CLASS_NAME%& operator=(const %CLASS_NAME%&) = delete;
			%CLASS_NAME%& operator=(%CLASS_NAME%&&) = delete;

		private:
	};
}
]]


sourceTemplate = [[
#include <SerializationLib/%CLASS_PATH%.h>

namespace Serialization
{
}
]]