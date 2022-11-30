//
// Created by Moon on 2022/11/21.
//

#include "file_handler.h"

#include <fcntl.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cstdlib>

FileHandler::FileHandler() {}

FileHandler::~FileHandler() {}

RC FileHandler::create_file(const char* file_name) {
  RC rc = RC::SUCCESS;
  if (file_name == nullptr) {
    return RC::GENERIC_ERROR;
  } else if (!file_name_.empty()) {
    return RC::GENERIC_ERROR;
  } else if (access(file_name, F_OK) != -1) {
    return RC::GENERIC_ERROR;
  } else {
    int fd;
    fd = open(file_name, O_RDWR | O_CREAT | O_EXCL, S_IREAD | S_IWRITE);
    if (fd < 0) {
      rc = RC::GENERIC_ERROR;
    } else {
      file_name_ = file_name;
      close(fd);
    }
  }
  return rc;
}

RC FileHandler::open_file(const char* file_name) {
  RC rc = RC::SUCCESS;
  int fd;
  if (file_name == nullptr) {
    if (file_name_.empty()) {
      rc = RC::GENERIC_ERROR;
    } else {
      if ((fd = open(file_name_.c_str(), O_RDWR)) < 0) {
        rc = RC::GENERIC_ERROR;
      } else {
        fd_ = fd;
      }
    }
  } else {
    if (!file_name_.empty()) {
      rc = RC::GENERIC_ERROR;
    } else {
      if ((fd = open(file_name, O_RDWR)) < 0) {
        return RC::GENERIC_ERROR;
      } else {
        file_name_ = file_name;
        fd_ = fd;
      }
    }
  }

  return rc;
}

RC FileHandler::close_file() {
  RC rc = RC::SUCCESS;
  if (fd_ >= 0) {
    if (close(fd_) < 0) {
      rc = RC::GENERIC_ERROR;
    } else {
      fd_ = -1;
    }
  }

  return rc;
}

RC FileHandler::remove_file(const char* file_name) {
  RC rc = RC::SUCCESS;
  if (file_name != nullptr) {
    if (remove(file_name) == 0) {
    } else {
      rc = RC::GENERIC_ERROR;
    }
  } else if (!file_name_.empty()) {
    if (fd_ < 0 || (rc = close_file()) == RC::SUCCESS) {
      if (remove(file_name_.c_str()) == 0) {
      } else {
        rc = RC::GENERIC_ERROR;
      }
    }
  }

  return rc;
}

RC FileHandler::write_file(int size, const char* data, int64_t* out_size) {
  RC rc = RC::SUCCESS;
  if (file_name_.empty()) {
    rc = RC::GENERIC_ERROR;
  } else if (fd_ < 0) {
    rc = RC::GENERIC_ERROR;
  } else {
    int64_t write_size = 0;
    if ((write_size = write(fd_, data, size)) != size) {
      rc = RC::GENERIC_ERROR;
    }
    if (out_size != nullptr) {
      *out_size = write_size;
    }
  }

  return rc;
}

RC FileHandler::write_at(uint64_t offset, int size, const char* data, int64_t* out_size) {
  RC rc = RC::SUCCESS;
  if (file_name_.empty()) {
    rc = RC::GENERIC_ERROR;
  } else if (fd_ < 0) {
    rc = RC::GENERIC_ERROR;
  } else {
    if (lseek(fd_, offset, SEEK_SET) == off_t(-1)) {
      rc = RC::GENERIC_ERROR;
    } else {
      int64_t write_size = 0;
      if ((write_size = write(fd_, data, size)) != size) {
        rc = RC::GENERIC_ERROR;
      }
      if (out_size != nullptr) {
        *out_size = write_size;
      }
    }
  }

  return rc;
}

RC FileHandler::append(int size, const char* data, int64_t* out_size) {
  RC rc = RC::SUCCESS;
  if (file_name_.empty()) {
    rc = RC::GENERIC_ERROR;
  } else if (fd_ < 0) {
    rc = RC::GENERIC_ERROR;
  } else {
    if (lseek(fd_, 0, SEEK_END) == off_t(-1)) {
      rc = RC::GENERIC_ERROR;
    } else {
      int64_t write_size = 0;
      if ((write_size = write(fd_, data, size)) != size) {
        rc = RC::GENERIC_ERROR;
      }
      if (out_size != nullptr) {
        *out_size = write_size;
      }
    }
  }

  return rc;
}

RC FileHandler::read_file(int size, char* data, int64_t* out_size) {
  RC rc = RC::SUCCESS;
  if (file_name_.empty()) {
    rc = RC::GENERIC_ERROR;
  } else if (fd_ < 0) {
    rc = RC::GENERIC_ERROR;
  } else {
    int64_t read_size = 0;
    if ((read_size = read(fd_, data, size)) != size) {
      rc = RC::GENERIC_ERROR;
    }
    if (out_size != nullptr) {
      *out_size = read_size;
    }
  }

  return rc;
}

RC FileHandler::read_at(uint64_t offset, int size, char* data, int64_t* out_size) {
  RC rc = RC::SUCCESS;
  if (file_name_.empty()) {
    rc = RC::GENERIC_ERROR;
  } else if (fd_ < 0) {
    rc = RC::GENERIC_ERROR;
  } else {
    if (lseek(fd_, offset, SEEK_SET) == off_t(-1)) {
      return RC::GENERIC_ERROR;
    } else {
      int64_t read_size = 0;
      if ((read_size = read(fd_, data, size)) != size) {
        rc = RC::GENERIC_ERROR;
      }
      if (out_size != nullptr) {
        *out_size = read_size;
      }
    }
  }

  return rc;
}

RC FileHandler::seek(uint64_t offset) {
  RC rc = RC::SUCCESS;
  if (file_name_.empty()) {
    rc = RC::GENERIC_ERROR;
  } else if (fd_ < 0) {
    rc = RC::GENERIC_ERROR;
  } else if (lseek(fd_, offset, SEEK_SET) == off_t(-1)) {
    rc = RC::GENERIC_ERROR;
  }
  return rc;
}
