<<<<<<< HEAD
#ifdef USE_LMDB
=======
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
#include "caffe/util/db_lmdb.hpp"

#include <sys/stat.h>

#include <string>

namespace caffe { namespace db {

<<<<<<< HEAD
void LMDB::Open(const string& source, Mode mode) {
  MDB_CHECK(mdb_env_create(&mdb_env_));
  if (mode == NEW) {
    CHECK_EQ(mkdir(source.c_str(), 0744), 0) << "mkdir " << source << " failed";
=======
const size_t LMDB_MAP_SIZE = 1099511627776;  // 1 TB

void LMDB::Open(const string& source, Mode mode) {
  MDB_CHECK(mdb_env_create(&mdb_env_));
  MDB_CHECK(mdb_env_set_mapsize(mdb_env_, LMDB_MAP_SIZE));
  if (mode == NEW) {
    CHECK_EQ(mkdir(source.c_str(), 0744), 0) << "mkdir " << source << "failed";
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
  }
  int flags = 0;
  if (mode == READ) {
    flags = MDB_RDONLY | MDB_NOTLS;
  }
<<<<<<< HEAD
  int rc = mdb_env_open(mdb_env_, source.c_str(), flags, 0664);
#ifndef ALLOW_LMDB_NOLOCK
  MDB_CHECK(rc);
#else
  if (rc == EACCES) {
    LOG(WARNING) << "Permission denied. Trying with MDB_NOLOCK ...";
    // Close and re-open environment handle
    mdb_env_close(mdb_env_);
    MDB_CHECK(mdb_env_create(&mdb_env_));
    // Try again with MDB_NOLOCK
    flags |= MDB_NOLOCK;
    MDB_CHECK(mdb_env_open(mdb_env_, source.c_str(), flags, 0664));
  } else {
    MDB_CHECK(rc);
  }
#endif
  LOG_IF(INFO, Caffe::root_solver()) << "Opened lmdb " << source;
=======
  MDB_CHECK(mdb_env_open(mdb_env_, source.c_str(), flags, 0664));
  LOG(INFO) << "Opened lmdb " << source;
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
}

LMDBCursor* LMDB::NewCursor() {
  MDB_txn* mdb_txn;
  MDB_cursor* mdb_cursor;
  MDB_CHECK(mdb_txn_begin(mdb_env_, NULL, MDB_RDONLY, &mdb_txn));
  MDB_CHECK(mdb_dbi_open(mdb_txn, NULL, 0, &mdb_dbi_));
  MDB_CHECK(mdb_cursor_open(mdb_txn, mdb_dbi_, &mdb_cursor));
  return new LMDBCursor(mdb_txn, mdb_cursor);
}

LMDBTransaction* LMDB::NewTransaction() {
<<<<<<< HEAD
  return new LMDBTransaction(mdb_env_);
}

void LMDBTransaction::Put(const string& key, const string& value) {
  keys.push_back(key);
  values.push_back(value);
}

void LMDBTransaction::Commit() {
  MDB_dbi mdb_dbi;
  MDB_val mdb_key, mdb_data;
  MDB_txn *mdb_txn;

  // Initialize MDB variables
  MDB_CHECK(mdb_txn_begin(mdb_env_, NULL, 0, &mdb_txn));
  MDB_CHECK(mdb_dbi_open(mdb_txn, NULL, 0, &mdb_dbi));

  for (int i = 0; i < keys.size(); i++) {
    mdb_key.mv_size = keys[i].size();
    mdb_key.mv_data = const_cast<char*>(keys[i].data());
    mdb_data.mv_size = values[i].size();
    mdb_data.mv_data = const_cast<char*>(values[i].data());

    // Add data to the transaction
    int put_rc = mdb_put(mdb_txn, mdb_dbi, &mdb_key, &mdb_data, 0);
    if (put_rc == MDB_MAP_FULL) {
      // Out of memory - double the map size and retry
      mdb_txn_abort(mdb_txn);
      mdb_dbi_close(mdb_env_, mdb_dbi);
      DoubleMapSize();
      Commit();
      return;
    }
    // May have failed for some other reason
    MDB_CHECK(put_rc);
  }

  // Commit the transaction
  int commit_rc = mdb_txn_commit(mdb_txn);
  if (commit_rc == MDB_MAP_FULL) {
    // Out of memory - double the map size and retry
    mdb_dbi_close(mdb_env_, mdb_dbi);
    DoubleMapSize();
    Commit();
    return;
  }
  // May have failed for some other reason
  MDB_CHECK(commit_rc);

  // Cleanup after successful commit
  mdb_dbi_close(mdb_env_, mdb_dbi);
  keys.clear();
  values.clear();
}

void LMDBTransaction::DoubleMapSize() {
  struct MDB_envinfo current_info;
  MDB_CHECK(mdb_env_info(mdb_env_, &current_info));
  size_t new_size = current_info.me_mapsize * 2;
  DLOG(INFO) << "Doubling LMDB map size to " << (new_size>>20) << "MB ...";
  MDB_CHECK(mdb_env_set_mapsize(mdb_env_, new_size));
=======
  MDB_txn* mdb_txn;
  MDB_CHECK(mdb_txn_begin(mdb_env_, NULL, 0, &mdb_txn));
  MDB_CHECK(mdb_dbi_open(mdb_txn, NULL, 0, &mdb_dbi_));
  return new LMDBTransaction(&mdb_dbi_, mdb_txn);
}

void LMDBTransaction::Put(const string& key, const string& value) {
  MDB_val mdb_key, mdb_value;
  mdb_key.mv_data = const_cast<char*>(key.data());
  mdb_key.mv_size = key.size();
  mdb_value.mv_data = const_cast<char*>(value.data());
  mdb_value.mv_size = value.size();
  MDB_CHECK(mdb_put(mdb_txn_, *mdb_dbi_, &mdb_key, &mdb_value, 0));
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
}

}  // namespace db
}  // namespace caffe
<<<<<<< HEAD
#endif  // USE_LMDB
=======
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
