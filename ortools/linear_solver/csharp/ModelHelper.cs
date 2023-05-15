namespace Google.OrTools.LinearSolver
{
    using System;
    using System.Collections.Generic;

    public partial class Model
    {
        public delegate Variable[] VariableMakerDelegate(Model model);
        public delegate Constraint[] ConstraintMakerDelegate(Model model);
    }
}
