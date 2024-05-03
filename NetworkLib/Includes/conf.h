#pragma once

/// <summary>
/// Defines the module type flag for FTP.
/// </summary>
#define FTP_MODULE 1

/// <summary>
/// Defines the module type flag for SMTP.
/// </summary>
#define SMTP_MODULE 2

/// <summary>
/// Defines the module type flag for Telnet.
/// </summary>
#define TELNET_MODULE 4

/// <summary>
/// Defines the maximum number of worker threads allowed.
/// </summary>
#define WORKER_THREADS_MAX 20

/// <summary>
/// Defines the minimum number of worker threads required.
/// </summary>
#define WORKER_THREADS_MIN 5

/// <summary>
/// Special value indicating all worker threads should be terminated.
/// </summary>
#define WORKER_THREADS_ALL 0
