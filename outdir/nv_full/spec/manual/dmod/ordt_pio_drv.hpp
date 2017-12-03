//   Ordt 170915.01 autogenerated file 
//   Input: test.rdl
//   Parms: test.parms
//   Date: Sun Dec 03 11:10:53 JST 2017
//

#ifndef __ORDT_PIO_DRV_HPP_INCLUDED__
#define __ORDT_PIO_DRV_HPP_INCLUDED__

#include <list>
#include <iostream>
#include <memory>
#include <cstdint>
#include <algorithm>
#include <string>
#include <sstream>
#define quote(x) #x

class ordt_drv_path_element {
  public:
    std::string m_name;
    int m_idx;
    ordt_drv_path_element(std::string _m_name, int _m_idx);
};

class ordt_drv_field {
  public:
    std::string m_name;
    int m_loidx;
    int m_width;
    bool m_readable;
    bool m_writeable;
    ordt_drv_field(std::string _m_name, int _m_loidx, int _m_width, bool _m_readable, bool _m_writeable);
};

class ordt_drv_element {
  private:
    std::list<std::string> split(const std::string &text, char sep, bool trim_rb);
  protected:
    int get_version(const std::string tag);
    std::list<ordt_drv_path_element> get_path(const std::string pathstr);
  public:
    std::string m_name;
    ordt_drv_element(std::string _m_name);
    virtual int get_address_using_list(const int version, std::list<ordt_drv_path_element> &path, const bool bypass_names, uint64_t &address, std::list<ordt_drv_field> &fields) = 0;
    virtual int get_address_using_version(const int version, const std::string pathstr, uint64_t &address, std::list<ordt_drv_field> &fields);
    std::vector<std::string> get_tags();
    int get_address(const std::string tag, const std::string pathstr, uint64_t &address, std::list<ordt_drv_field> &fields);
};

class ordt_drv_regset_child {
  public:
    int m_map;
    std::shared_ptr<ordt_drv_element> m_child;
    int m_reps;
    uint64_t m_offset;
    uint64_t m_stride;
    ordt_drv_regset_child(int _m_map, std::shared_ptr<ordt_drv_element> _m_child, int _m_reps, uint64_t _m_offset, uint64_t _m_stride);
};

class ordt_drv_regset : public ordt_drv_element {
  protected:
    std::list<ordt_drv_regset_child> m_children;
  public:
    ordt_drv_regset(std::string _m_name);
    virtual int get_address_using_list(const int version, std::list<ordt_drv_path_element> &path, const bool bypass_names, uint64_t &address, std::list<ordt_drv_field> &fields);
    void add_child(int _m_map, std::shared_ptr<ordt_drv_element> _m_child, int _m_reps, uint64_t _m_offset, uint64_t _m_stride);
};

class ordt_drv_reg : public ordt_drv_element {
  protected:
    std::list<ordt_drv_field> m_fields;
  public:
    ordt_drv_reg(std::string _m_name);
    virtual int get_address_using_list(const int version, std::list<ordt_drv_path_element> &path, const bool bypass_names, uint64_t &address, std::list<ordt_drv_field> &fields);
    void add_field(std::string _m_name, int _m_loidx, int _width, bool _m_readable, bool _m_writeable);
};

class ordt_drv_root : public ordt_drv_regset {
  public:
    ordt_drv_root();
    void build();
    virtual int get_address_using_version(const int version, const std::string pathstr, uint64_t &address, std::list<ordt_drv_field> &fields);
};

#endif // __ORDT_PIO_DRV_HPP_INCLUDED__
