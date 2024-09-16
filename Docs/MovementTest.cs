using AutomationTool;
using Gauntlet;

namespace MovementTest.Automation
{
	public class MovementTest : UnrealTestNode<UnrealTestConfiguration>
	{
		public MovementTest(UnrealTestContext InContext)
			: base(InContext)
		{
		}

		private readonly string ControllerName = "MovmentGauntletTestController";

		public override UnrealTestConfiguration GetConfiguration()
		{
			UnrealTestConfiguration Config = base.GetConfiguration();

			// Obtener un rol de cliente único
			UnrealTestRole ClientRole = Config.RequireRole(UnrealTargetRole.Client);

			// Agregar el controlador personalizado que manejará la prueba
			ClientRole.Controllers.Add(ControllerName);

			// Establecer el tiempo máximo de duración para el test
			Config.MaxDuration = 60; // en segundos

			return Config;
		}
	}
}
