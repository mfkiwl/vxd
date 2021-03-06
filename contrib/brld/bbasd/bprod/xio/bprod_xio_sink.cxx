// This is basic/bprod/xio/bprod_xio_sink.cxx

//:
// \file

#include <bprod/xio/bprod_xio_sink.h>
#include <bxml/bxml_write.h>


//: Constructor
bprod_xio_sink::bprod_xio_sink()
  : os_()
{
}


//: Constructor
bprod_xio_sink::bprod_xio_sink(const vcl_string& filename)
  : os_(filename.c_str())
{
  write_header();
}


//: Destructor
bprod_xio_sink::~bprod_xio_sink()
{
  if(os_.good())
    write_footer();
  os_.close();
}


//: Open a new file
bool bprod_xio_sink::open(const vcl_string& filename)
{
  if(os_.good())
    write_footer();
  os_.close();

  os_.open(filename.c_str());

  if(!os_.good())
    return false;

  write_header();
  return true;
}


//: Runs the process
bprod_signal bprod_xio_sink::execute()
{
  if(!os_.is_open())
    return BPROD_INVALID;

  if(!os_.good())
    return BPROD_INVALID;

  assert(input_type_id(0) == typeid(bxml_data_sptr));
  bxml_data_sptr data = input<bxml_data_sptr>(0);
  if(!data)
    return BPROD_INVALID;

  bxml_write_data(os_, data);
  os_ << "\n" << vcl_flush;

  return BPROD_VALID;
}


void bprod_xio_sink::write_header()
{
  bxml_write_declaration(os_, bxml_document() );
  os_ << "<stream>\n" << vcl_flush;
}


void bprod_xio_sink::write_footer()
{
  os_ << "\n</stream>\n" << vcl_flush;
}
