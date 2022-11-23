// MIT License

// Copyright (c) 2022 Shac Ron

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// SPDX-License-Identifier: MIT License

#include <errno.h>
#include <string.h>
#include <stdio.h>

// Darwin errlist
const char * const sys_errlist[] = {
  [0] = "Undefined error: 0",
  [EPERM] = "Operation not permitted",
  [ENOENT] = "No such file or directory",
  [ESRCH] = "No such process",
  [EINTR] = "Interrupted system call",
  [EIO] = "Input/output error",
  [ENXIO] = "Device not configured",
  [E2BIG] = "Argument list too long",
  [ENOEXEC] = "Exec format error",
  [EBADF] = "Bad file descriptor",
  [ECHILD] = "No child processes",
  [EDEADLK] = "Resource deadlock avoided",
  [ENOMEM] = "Cannot allocate memory",
  [EACCES] = "Permission denied",
  [EFAULT] = "Bad address",
  [ENOTBLK] = "Block device required",
  [EBUSY] = "Resource busy",
  [EEXIST] = "File exists",
  [EXDEV] = "Cross-device link",
  [ENODEV] = "Operation not supported by device",
  [ENOTDIR] = "Not a directory",
  [EISDIR] = "Is a directory",
  [EINVAL] = "Invalid argument",
  [ENFILE] = "Too many open files in system",
  [EMFILE] = "Too many open files",
  [ENOTTY] = "Inappropriate ioctl for device",
  [ETXTBSY] = "Text file busy",
  [EFBIG] = "File too large",
  [ENOSPC] = "No space left on device",
  [ESPIPE] = "Illegal seek",
  [EROFS] = "Read-only file system",
  [EMLINK] = "Too many links",
  [EPIPE] = "Broken pipe",
  [EDOM] = "Numerical argument out of domain",
  [ERANGE] = "Result too large",
  [EAGAIN] = "Resource temporarily unavailable",
  [EINPROGRESS] = "Operation now in progress",
  [EALREADY] = "Operation already in progress",
  [ENOTSOCK] = "Socket operation on non-socket",
  [EDESTADDRREQ] = "Destination address required",
  [EMSGSIZE] = "Message too long",
  [EPROTOTYPE] = "Protocol wrong type for socket",
  [ENOPROTOOPT] = "Protocol not available",
  [EPROTONOSUPPORT] = "Protocol not supported",
  [ESOCKTNOSUPPORT] = "Socket type not supported",
  [ENOTSUP] = "Operation not supported",
  [EPFNOSUPPORT] = "Protocol family not supported",
  [EAFNOSUPPORT] = "Address family not supported by protocol family",
  [EADDRINUSE] = "Address already in use",
  [EADDRNOTAVAIL] = "Can't assign requested address",
  [ENETDOWN] = "Network is down",
  [ENETUNREACH] = "Network is unreachable",
  [ENETRESET] = "Network dropped connection on reset",
  [ECONNABORTED] = "Software caused connection abort",
  [ECONNRESET] = "Connection reset by peer",
  [ENOBUFS] = "No buffer space available",
  [EISCONN] = "Socket is already connected",
  [ENOTCONN] = "Socket is not connected",
  [ESHUTDOWN] = "Can't send after socket shutdown",
  [ETOOMANYREFS] = "Too many references: can't splice",
  [ETIMEDOUT] = "Operation timed out",
  [ECONNREFUSED] = "Connection refused",
  [ELOOP] = "Too many levels of symbolic links",
  [ENAMETOOLONG] = "File name too long",
  [EHOSTDOWN] = "Host is down",
  [EHOSTUNREACH] = "No route to host",
  [ENOTEMPTY] = "Directory not empty",
  [EPROCLIM] = "Too many processes",
  [EUSERS] = "Too many users",
  [EDQUOT] = "Disc quota exceeded",
  [ESTALE] = "Stale NFS file handle",
  [EREMOTE] = "Too many levels of remote in path",
  [EBADRPC] = "RPC struct is bad",
  [ERPCMISMATCH] = "RPC version wrong",
  [EPROGUNAVAIL] = "RPC prog. not avail",
  [EPROGMISMATCH] = "Program version wrong",
  [EPROCUNAVAIL] = "Bad procedure for program",
  [ENOLCK] = "No locks available",
  [ENOSYS] = "Function not implemented",
  [EFTYPE] = "Inappropriate file type or format",
  [EAUTH] = "Authentication error",
  [ENEEDAUTH] = "Need authenticator",
  [EPWROFF] = "Device power is off",
  [EDEVERR] = "Device error",
  [EOVERFLOW] = "Value too large to be stored in data type",
  [EBADEXEC] = "Bad executable (or shared library)",
  [EBADARCH] = "Bad CPU type in executable",
  [ESHLIBVERS] = "Shared library version mismatch",
  [EBADMACHO] = "Malformed Mach-o file",
  [ECANCELED] = "Operation canceled",
  [EIDRM] = "Identifier removed",
  [ENOMSG] = "No message of desired type",
  [EILSEQ] = "Illegal byte sequence",
  [ENOATTR] = "Attribute not found",
  [EBADMSG] = "Bad message",
  [EMULTIHOP] = "EMULTIHOP (Reserved)",
  [ENODATA] = "No message available on stream",
  [ENOLINK] = "ENOLINK (Reserved)",
  [ENOSR] = "No stream resources",
  [ENOSTR] = "Not a stream",
  [EPROTO] = "Protocol error",
  [ETIME] = "Stream ioctl timeout",
  [EOPNOTSUPP] = "Operation not supported on socket",
  [ENOPOLICY] = "Policy not found",
  [ENOTRECOVERABLE] = "State not recoverable",
  [EOWNERDEAD] = "Previous owner died",
  [EQFULL] = "Interface output queue is full",
};
const int sys_nerr = sizeof(sys_errlist) / sizeof(sys_errlist[0]);

char *strerror(int errnum) {
  // On error, a pointer to static buffer containing "Unknown error: <errnum>"
  // is expected. This is not thread-safe and is avoided by this function.
  if (errnum >= sys_nerr) return "Unknown error";
  return (char*)sys_errlist[errnum];
}
