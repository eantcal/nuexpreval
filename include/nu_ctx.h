//  
// This file is part of nuExprEval
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//

/* -------------------------------------------------------------------------- */

#ifndef __NU_CTX_H__
#define __NU_CTX_H__


/* -------------------------------------------------------------------------- */

#include "nu_symbol_map.h"
#include "nu_variant.h"


/* -------------------------------------------------------------------------- */

namespace nu {


/* -------------------------------------------------------------------------- */

/**
 * This class holds the value of variables
 */
class ctx_t : public symbol_map_t<std::string, variant_t> {
public:
    using handle_t = std::shared_ptr<ctx_t>;

    ctx_t() = default;
    ctx_t(const ctx_t&) = default;
    ctx_t& operator=(const ctx_t&) = default;
    
    bool define(const std::string& name, const variant_t& value) {
        map()[name] = value;
        return true;
    }

    friend std::stringstream& operator<<(std::stringstream& ss, ctx_t& obj)  {
        for (const auto& e : obj.map()) {
            ss << "\t" << e.first << ": "
                << " "
                << e.second << std::endl;
        }

        return ss;
    }

protected:
    virtual void get_err_msg(const std::string& key, std::string& err) const {
        err = "'" + key + "' out of scope";
    }

};


/* -------------------------------------------------------------------------- */

}


/* -------------------------------------------------------------------------- */

#endif // __NU_VAR_SCOPE_H__
