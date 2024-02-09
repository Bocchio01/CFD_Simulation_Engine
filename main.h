// String values are not used as default but hard written in the code. Must be fixed

#define DEFAULT_IN_FILE_PATH "data"   // Input file path
#define DEFAULT_IN_FILE_NAME "input"  // Input file name
#define DEFAULT_IN_FILE_FORMAT "JSON" // Input file format

#define DEFAULT_IN_ULID 1.0       // Lid velocity
#define DEFAULT_IN_GEOMETRY_X 1.0 // Geometry X
#define DEFAULT_IN_GEOMETRY_Y 1.0 // Geometry Y
#define DEFAULT_IN_FLUID_MU 1     // Fluid viscosity
#define DEFAULT_IN_FLUID_RE 1     // Reynolds number

#define DEFAULT_ENGINE_MESH_TYPE "STAGGERED"            // Mesh type
#define DEFAULT_ENGINE_MESH_NODES_X 100                 // Mesh nodes X
#define DEFAULT_ENGINE_MESH_NODES_Y 100                 // Mesh nodes Y
#define DEFAULT_ENGINE_MESH_ELEMENTS_TYPE "RECTANGULAR" // Elements type

#define DEFAULT_ENGINE_METHOD_TYPE "SCGS"            // Method type
#define DEFAULT_ENGINE_METHOD_TOLERANCE 1e-4         // Method tolerance
#define DEFAULT_ENGINE_METHOD_MAX_ITER 1000          // Method max iterations
#define DEFAULT_ENGINE_METHOD_UNDER_RELAXATION_U 0.5 // Method under relaxation u
#define DEFAULT_ENGINE_METHOD_UNDER_RELAXATION_V 0.5 // Method under relaxation v
#define DEFAULT_ENGINE_METHOD_UNDER_RELAXATION_P 0.3 // Method under relaxation p

#define DEFAULT_ENGINE_SCHEMES_CONVECTION "UDS"         // Schemes convection
#define DEFAULT_ENGINE_SCHEMES_DIFFUSION "SECOND_ORDER" // Schemes diffusion

#define DEFAULT_OUT_FILE_PATH "data"   // Output file path
#define DEFAULT_OUT_FILE_NAME "output" // Output file name
#define DEFAULT_OUT_FILE_FORMAT "JSON" // Output file format
