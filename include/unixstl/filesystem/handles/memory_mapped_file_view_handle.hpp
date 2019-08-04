/* /////////////////////////////////////////////////////////////////////////
 * File:        unixstl/filesystem/handles/memory_mapped_file_view_handle.hpp
 *
 * Purpose:     Handle::Ref+Wrapper handle-adapter class template for
 *              UNIX memory mapped file view handles.
 *
 * Created:     1st January 2017
 * Updated:     2nd February 2019
 *
 * Home:        http://stlsoft.org/
 *
 * Copyright (c) 2017, Matthew Wilson and Synesis Software
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - Neither the name(s) of Matthew Wilson and Synesis Software nor the
 *   names of any contributors may be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ////////////////////////////////////////////////////////////////////// */


/** \file unixstl/filesystem/handles/memory_mapped_file_view_handle.hpp
 *
 * \brief [C++ only] Definition of the unixstl::memory_mapped_file_view_handle class
 *   template (\ref group__library__FileSystem "File System" Library).
 */

#ifndef UNIXSTL_INCL_UNIXSTL_FILESYSTEM_HANDLES_HPP_MEMORY_MAPPED_FILE_VIEW_HANDLE
#define UNIXSTL_INCL_UNIXSTL_FILESYSTEM_HANDLES_HPP_MEMORY_MAPPED_FILE_VIEW_HANDLE

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define UNIXSTL_VER_UNIXSTL_FILESYSTEM_HANDLES_HPP_MEMORY_MAPPED_FILE_VIEW_HANDLE_MAJOR      1
# define UNIXSTL_VER_UNIXSTL_FILESYSTEM_HANDLES_HPP_MEMORY_MAPPED_FILE_VIEW_HANDLE_MINOR      0
# define UNIXSTL_VER_UNIXSTL_FILESYSTEM_HANDLES_HPP_MEMORY_MAPPED_FILE_VIEW_HANDLE_REVISION   6
# define UNIXSTL_VER_UNIXSTL_FILESYSTEM_HANDLES_HPP_MEMORY_MAPPED_FILE_VIEW_HANDLE_EDIT       10
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifndef UNIXSTL_INCL_UNIXSTL_H_UNIXSTL
# include <unixstl/unixstl.h>
#endif /* !UNIXSTL_INCL_UNIXSTL_H_UNIXSTL */
#ifdef STLSOFT_TRACE_INCLUDE
# pragma message(__FILE__)
#endif /* STLSOFT_TRACE_INCLUDE */

#ifndef UNIXSTL_INCL_UNIXSTL_SYNCH_H_ATOMIC_TYPES
# include <unixstl/synch/atomic_types.h>
#endif /* !UNIXSTL_INCL_UNIXSTL_SYNCH_H_ATOMIC_TYPES */
#ifndef STLSOFT_INCL_STLSOFT_SMARTPTR_HPP_REF_PTR
# include <stlsoft/smartptr/ref_ptr.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_SMARTPTR_HPP_REF_PTR */

#ifndef STLSOFT_INCL_STLSOFT_QUALITY_H_CONTRACT
# include <stlsoft/quality/contract.h>
#endif /* !STLSOFT_INCL_STLSOFT_QUALITY_H_CONTRACT */
#ifndef STLSOFT_INCL_STLSOFT_QUALITY_H_COVER
# include <stlsoft/quality/cover.h>
#endif /* !STLSOFT_INCL_STLSOFT_QUALITY_H_COVER */

#ifndef STLSOFT_INCL_SYS_H_MMAN
# define STLSOFT_INCL_SYS_H_MMAN
# include <sys/mman.h>
#endif /* !STLSOFT_INCL_SYS_H_MMAN */

/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef UNIXSTL_NO_NAMESPACE
# if defined(STLSOFT_NO_NAMESPACE) || \
     defined(STLSOFT_DOCUMENTATION_SKIP_SECTION)
/* There is no stlsoft namespace, so must define ::unixstl */
namespace unixstl
{
# else
/* Define stlsoft::unixstl_project */

namespace stlsoft
{
namespace unixstl_project
{

# endif /* STLSOFT_NO_NAMESPACE */
#endif /* !UNIXSTL_NO_NAMESPACE */

/* /////////////////////////////////////////////////////////////////////////
 * classes
 */

/** Raw structure that represents a memory-mapped file view state
 */
struct memory_mapped_file_view_state_t
{
    /// Pointer to the base of the view, or NULL if not mapped
    void* const         memory;
    /// Size of the view
    us_uintptr_t const  size;

public:
    /// Constructs an instance of the view
    memory_mapped_file_view_state_t(void* p, us_uintptr_t n)
        : memory(p)
        , size(n)
    {}
private:
    void operator =(memory_mapped_file_view_state_t const&);    // copy-assignment proscribed
};

/** A Handle::Ref+Wrapper handle adaptor class template for memory mapped
 * file views.
 *
 * \param R The reference counting policy that determines how the type's
 *   reference count will be manipulated.
 */
template <ss_typename_param_k R>
struct memory_mapped_file_view_handle
{
public: // Member Types
    /// The handle type
    typedef memory_mapped_file_view_state_t       handle_type;
    /// The reference count policy type
    typedef R                                     refcount_policy;
    /// This type
    typedef memory_mapped_file_view_handle<R>     class_type;

    /// The Handle::Ref+Wrapper <strong>Handle</strong> type.
    ///
    /// \note This type is mandatory to the pattern.
    typedef memory_mapped_file_view_state_t       HRW_Handle_type;
    /// The Handle::Ref+Wrapper <strong>Ref</strong> type.
    ///
    /// \note This type is mandatory to the pattern.
    typedef stlsoft::ref_ptr<class_type>          HRW_Ref_type;

    typedef HRW_Handle_type                       Handle;
    typedef HRW_Ref_type                          Ref;

public: // Construction

    /// Creates an instance of the ref from the underlying state types.
    static Ref create(handle_type h)
    {
        return Ref(new class_type(h, true), false);
    }
    /// Creates an instance of the ref from the underlying state types.
    static Ref create(void* memory, us_uintptr_t size)
    {
        return create(handle_type(memory, size));
    }
    /// Destroys an instance of the underlying handle type
    static void destroy(handle_type h)
    {
        if(NULL != h.memory)
        {
            STLSOFT_NS_GLOBAL(munmap)(h.memory, h.size);
        }
    }

private:
    memory_mapped_file_view_handle(handle_type h, bool isOwner)
        : handle(h)
        , refCount(1)
        , isOwner(isOwner)
    {}
private:
    class_type& operator =(class_type const &);

public: // Reference-counting Operations
    /// Adds/increment the reference
    memory_mapped_file_view_handle* AddRef()
    {
        refcount_policy::addref(refCount);

        return this;
    }

    /// Releases/decrements the reference
    void Release()
    {
        if(0 == refcount_policy::release(refCount))
        {
            if(isOwner)
            {
                destroy(handle);
            }
            delete this;
        }
    }

public: // Member Variables
    /// The handle value
    handle_type     handle;
private:
    atomic_int_t    refCount;
    const bool      isOwner;
};

/* /////////////////////////////////////////////////////////////////////////
 * shims
 */

/** Elicits a file-stream handle (<code>FILE*</code>) from the given
 * instance.
 */
template <ss_typename_param_k R>
inline
ss_typename_type_k memory_mapped_file_view_handle<R>::handle_type const
get_memory_mapped_file_view_handle(
    memory_mapped_file_view_handle<R>& h
)
{
    return h.handle;
}

/** Elicits a file-stream handle (<code>FILE*</code>) from the given
 * instance.
 */
template <ss_typename_param_k R>
inline
ss_typename_type_k memory_mapped_file_view_handle<R>::handle_type const
get_memory_mapped_file_view_handle(
    memory_mapped_file_view_handle<R>* h
)
{
    return (NULL != h) ? h->handle : ss_typename_type_k memory_mapped_file_view_handle<R>::handle_type(NULL, 0u);
}

/* ////////////////////////////////////////////////////////////////////// */

#ifndef UNIXSTL_NO_NAMESPACE
# if defined(STLSOFT_NO_NAMESPACE) || \
     defined(STLSOFT_DOCUMENTATION_SKIP_SECTION)
} /* namespace unixstl */
# else
} /* namespace unixstl_project */
} /* namespace stlsoft */
# endif /* STLSOFT_NO_NAMESPACE */
#endif /* !UNIXSTL_NO_NAMESPACE */

/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !UNIXSTL_INCL_UNIXSTL_FILESYSTEM_HANDLES_HPP_MEMORY_MAPPED_FILE_VIEW_HANDLE */

/* ///////////////////////////// end of file //////////////////////////// */

