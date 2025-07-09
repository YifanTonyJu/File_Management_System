import { createRouter, createWebHistory } from 'vue-router'
import AddFile from '../views/AddFile.vue'
import DeleteFile from '../views/DeleteFile.vue'
import Home from '../views/Home.vue'
import QueryAll from '../views/QueryAll.vue'
import QueryByFileName from '../views/QueryByFileName.vue'
import QueryByUser from '../views/QueryByUser.vue'
import UpdateFile from '../views/UpdateFile.vue'

const routes = [
  {
    path: '/',
    name: 'Home',
    component: Home
  },
  {
    path: '/add',
    name: 'AddFile',
    component: AddFile
  },
  {
    path: '/delete',
    name: 'DeleteFile',
    component: DeleteFile
  },
  {
    path: '/update',
    name: 'UpdateFile',
    component: UpdateFile
  },
  {
    path: '/query',
    name: 'QueryAll',
    component: QueryAll
  },
  {
    path: '/query-user',
    name: 'QueryByUser',
    component: QueryByUser
  },
  {
    path: '/query-file',
    name: 'QueryByFileName',
    component: QueryByFileName
  }
]

const router = createRouter({
  history: createWebHistory(),
  routes
})

export default router
