export module xox.core.error.error_list;

/** Error List. Please never compare an error against FAILED
 * Either do result != OK , or !result. This way, Error fail
 * values can be more detailed in the future.
 *
 * This is a generic error list, mainly for organizing a language of returning errors.
 *
 * Errors:
 * - Are added to the Error enum in core/error/error_list.h
 * - Have a description added to error_names in core/error/error_list.cpp
 * - Are bound with BIND_CORE_ENUM_CONSTANT() in core/core_constants.cpp
 */

export typedef enum{
	OK, // (0)
	FAILED, ///< Generic fail error
	ERR_UNAVAILABLE, ///< What is requested is unsupported/unavailable
	ERR_UNCONFIGURED, ///< The object being used hasn't been properly set up yet
	ERR_UNAUTHORIZED, ///< Missing credentials for requested resource
	ERR_PARAMETER_RANGE_ERROR, ///< Parameter given out of range (5)
	ERR_OUT_OF_MEMORY, ///< Out of memory
	ERR_FILE_NOT_FOUND,
	ERR_FILE_BAD_DRIVE,
	ERR_FILE_BAD_PATH,
	ERR_FILE_NO_PERMISSION, // (10)
	ERR_FILE_ALREADY_IN_USE,
	ERR_FILE_CANT_OPEN,
	ERR_FILE_CANT_WRITE,
	ERR_FILE_CANT_READ,
	ERR_FILE_UNRECOGNIZED, // (15)
	ERR_FILE_CORRUPT,
	ERR_FILE_MISSING_DEPENDENCIES,
	ERR_FILE_EOF,
	ERR_CANT_OPEN, ///< Can't open a resource/socket/file
	ERR_CANT_CREATE, // (20)
	ERR_QUERY_FAILED,
	ERR_ALREADY_IN_USE,
	ERR_LOCKED, ///< resource is locked
	ERR_TIMEOUT,
	ERR_CANT_CONNECT, // (25)
	ERR_CANT_RESOLVE,
	ERR_CONNECTION_ERROR,
	ERR_CANT_ACQUIRE_RESOURCE,
	ERR_CANT_FORK,
	ERR_INVALID_DATA, ///< Data passed is invalid (30)
	ERR_INVALID_PARAMETER, ///< Parameter passed is invalid
	ERR_ALREADY_EXISTS, ///< When adding, item already exists
	ERR_DOES_NOT_EXIST, ///< When retrieving/erasing, if item does not exist
	ERR_DATABASE_CANT_READ, ///< database is full
	ERR_DATABASE_CANT_WRITE, ///< database is full (35)
	ERR_COMPILATION_FAILED,
	ERR_METHOD_NOT_FOUND,
	ERR_LINK_FAILED,
	ERR_SCRIPT_FAILED,
	ERR_CYCLIC_LINK, // (40)
	ERR_INVALID_DECLARATION,
	ERR_DUPLICATE_SYMBOL,
	ERR_PARSE_ERROR,
	ERR_BUSY,
	ERR_SKIP, // (45)
	ERR_HELP, ///< user requested help!!
	ERR_BUG, ///< a bug in the software certainly happened, due to a double check failing or unexpected behavior.
	ERR_PRINTER_ON_FIRE, /// the parallel port printer is engulfed in flames
	ERR_MAX, // Not being returned, value represents the number of errors
} Error;

export const char* error_names[] = {
	"OK", // OK
	"Failed", // FAILED
	"Unavailable", // ERR_UNAVAILABLE
	"Unconfigured", // ERR_UNCONFIGURED
	"Unauthorized", // ERR_UNAUTHORIZED
	"Parameter out of range", // ERR_PARAMETER_RANGE_ERROR
	"Out of memory", // ERR_OUT_OF_MEMORY
	"File not found", // ERR_FILE_NOT_FOUND
	"File: Bad drive", // ERR_FILE_BAD_DRIVE
	"File: Bad path", // ERR_FILE_BAD_PATH
	"File: Permission denied", // ERR_FILE_NO_PERMISSION
	"File already in use", // ERR_FILE_ALREADY_IN_USE
	"Can't open file", // ERR_FILE_CANT_OPEN
	"Can't write file", // ERR_FILE_CANT_WRITE
	"Can't read file", // ERR_FILE_CANT_READ
	"File unrecognized", // ERR_FILE_UNRECOGNIZED
	"File corrupt", // ERR_FILE_CORRUPT
	"Missing dependencies for file", // ERR_FILE_MISSING_DEPENDENCIES
	"End of file", // ERR_FILE_EOF
	"Can't open", // ERR_CANT_OPEN
	"Can't create", // ERR_CANT_CREATE
	"Query failed", // ERR_QUERY_FAILED
	"Already in use", // ERR_ALREADY_IN_USE
	"Locked", // ERR_LOCKED
	"Timeout", // ERR_TIMEOUT
	"Can't connect", // ERR_CANT_CONNECT
	"Can't resolve", // ERR_CANT_RESOLVE
	"Connection error", // ERR_CONNECTION_ERROR
	"Can't acquire resource", // ERR_CANT_ACQUIRE_RESOURCE
	"Can't fork", // ERR_CANT_FORK
	"Invalid data", // ERR_INVALID_DATA
	"Invalid parameter", // ERR_INVALID_PARAMETER
	"Already exists", // ERR_ALREADY_EXISTS
	"Does not exist", // ERR_DOES_NOT_EXIST
	"Can't read database", // ERR_DATABASE_CANT_READ
	"Can't write database", // ERR_DATABASE_CANT_WRITE
	"Compilation failed", // ERR_COMPILATION_FAILED
	"Method not found", // ERR_METHOD_NOT_FOUND
	"Link failed", // ERR_LINK_FAILED
	"Script failed", // ERR_SCRIPT_FAILED
	"Cyclic link detected", // ERR_CYCLIC_LINK
	"Invalid declaration", // ERR_INVALID_DECLARATION
	"Duplicate symbol", // ERR_DUPLICATE_SYMBOL
	"Parse error", // ERR_PARSE_ERROR
	"Busy", // ERR_BUSY
	"Skip", // ERR_SKIP
	"Help", // ERR_HELP
	"Bug", // ERR_BUG
	"Printer on fire", // ERR_PRINTER_ON_FIRE
};

static_assert(sizeof(error_names) / sizeof(*error_names) == ERR_MAX);