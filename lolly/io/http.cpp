
/******************************************************************************
 * MODULE     : http.cpp
 * DESCRIPTION: HTTP related routines
 * COPYRIGHT  : (C) 2023  Darcy Shen
 *******************************************************************************
 * This software falls under the GNU general public license version 3 or later.
 * It comes WITHOUT ANY WARRANTY WHATSOEVER. For details, see the file LICENSE
 * in the root directory or <http://www.gnu.org/licenses/gpl-3.0.html>.
 ******************************************************************************/

#include "http.hpp"
#include "lolly/data/uri.hpp"
#include "tree.hpp"

#include <httplib.h>

namespace lolly {
namespace io {

json
http_get (url u) {
  string          host= data::uri_host (u);
  string          path= data::uri_path (u);
  httplib::Client cli ((char*) c_string (host));
  auto            r= cli.Get ((char*) c_string (path));
  json            r_json;
  r_json.set ("status", r->status);
  r_json.set ("body", (r->body).c_str ());
  return r_json;
}

} // namespace io
} // namespace lolly
