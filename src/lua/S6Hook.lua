--[[ S6Hook v0.1a  // by yoq ]]--

function InstallS6Hook()
	if nil == string.find(Framework.GetProgramVersion(), "1.71.4289") then
		DEBUG_AddNote("S6Hook failed! Please install patch 1.71!");
	end

	local stage1 = "@@stage1.bin@@";
	local stage2 = "@@stage2.yx@@";
	local stage3 = "@@S6Hook.yx@@";
	
	local shrink = function(cc)
	 local o, n, max = {}, 1, string.len(cc)
		while n <= max do
			local b = string.byte(cc, n)
			if b >= 97 then b=16*(b-97)+string.byte(cc, n+1)-97; n=n+2; else b=b-65; n=n+1; end
			table.insert(o, string.char(b))
		end
		return table.concat(o)
	end
	
	local eID = Logic.CreateEntity(Entities.A_Chicken, 0, 0, 0, 1)
	Framework.WriteToLog(stage1);
	Logic.SetEntityScriptingValue(eID, -81, 4706264)
	Logic.DestroyEntity(eID, shrink(stage2), shrink(stage3))
	
	return S6Hook ~= nil
end