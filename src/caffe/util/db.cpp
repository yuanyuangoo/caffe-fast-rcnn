#include "caffe/util/db.hpp"
#include "caffe/util/db_leveldb.hpp"
#include "caffe/util/db_lmdb.hpp"

#include <string>

namespace caffe { namespace db {

DB* GetDB(DataParameter::DB backend) {
  switch (backend) {
<<<<<<< HEAD
#ifdef USE_LEVELDB
  case DataParameter_DB_LEVELDB:
    return new LevelDB();
#endif  // USE_LEVELDB
#ifdef USE_LMDB
  case DataParameter_DB_LMDB:
    return new LMDB();
#endif  // USE_LMDB
  default:
    LOG(FATAL) << "Unknown database backend";
    return NULL;
=======
  case DataParameter_DB_LEVELDB:
    return new LevelDB();
  case DataParameter_DB_LMDB:
    return new LMDB();
  default:
    LOG(FATAL) << "Unknown database backend";
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
  }
}

DB* GetDB(const string& backend) {
<<<<<<< HEAD
#ifdef USE_LEVELDB
  if (backend == "leveldb") {
    return new LevelDB();
  }
#endif  // USE_LEVELDB
#ifdef USE_LMDB
  if (backend == "lmdb") {
    return new LMDB();
  }
#endif  // USE_LMDB
  LOG(FATAL) << "Unknown database backend";
  return NULL;
=======
  if (backend == "leveldb") {
    return new LevelDB();
  } else if (backend == "lmdb") {
    return new LMDB();
  } else {
    LOG(FATAL) << "Unknown database backend";
  }
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
}

}  // namespace db
}  // namespace caffe
