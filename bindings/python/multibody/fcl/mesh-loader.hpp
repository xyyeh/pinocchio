//
// Copyright (c) 2017-2019 CNRS INRIA
//

#ifndef __pinocchio_python_fcl_mesh_loader_hpp__
#define __pinocchio_python_fcl_mesh_loader_hpp__

#include "pinocchio/spatial/fcl-pinocchio-conversions.hpp"
#include <hpp/fcl/mesh_loader/loader.h>

#include <boost/python.hpp>
#include <typeinfo>

namespace pinocchio
{
  namespace python
  {
    namespace fcl
    {
      
      namespace bp = boost::python;
      
      template<typename MeshLoader>
      struct MeshLoaderPythonVisitor
      : public bp::def_visitor< MeshLoaderPythonVisitor<MeshLoader> >
      {
        typedef boost::shared_ptr<MeshLoader> MeshLoaderPtr_t;
        
        template <typename T>
        static boost::shared_ptr<T> create()
        {
          return boost::shared_ptr<T>(new T);
        }

        template<class PyClass>
        void visit(PyClass& cl) const
        {
          cl
          .def("create",&MeshLoaderPythonVisitor::create<MeshLoader>,"Create a new object.")
          .staticmethod("create")
          ;
        }
        
        static void expose(const std::string & doc = "")
        {
          static const std::string class_name = typeid(MeshLoader).name();
          bp::class_<MeshLoader, MeshLoaderPtr_t>
            (class_name.c_str(),
             doc.c_str(),
             bp::init<>())
            .def(MeshLoaderPythonVisitor())
          ;
        }
        
      };
      
    } // namespace fcl
    
  } // namespace python
} // namespace pinocchio

#endif // namespace __pinocchio_python_fcl_mesh_loader_hpp__
