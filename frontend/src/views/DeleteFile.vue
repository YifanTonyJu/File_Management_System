<template>
  <div>
    <router-link to="/">← Back</router-link>
    <h1>Delete File</h1>
    
    <input v-model="fileName" placeholder="File name">
    <button @click="deleteFile">Delete File</button>

    <p v-if="message">{{ message }}</p>
  </div>
</template>

<script setup>
import { ref } from 'vue'

const message = ref('')
const fileName = ref('')

const deleteFile = async () => {
  try {
    if (!fileName.value) {
      message.value = 'Please enter file name to delete'
      return
    }
    
    const response = await fetch(`/api/files/${fileName.value}`, {
      method: 'DELETE'
    })
    
    if (!response.ok) {
      throw new Error(`HTTP ${response.status}: ${response.statusText}`)
    }
    
    message.value = 'File deleted successfully!'
    fileName.value = ''
    
  } catch (error) {
    message.value = `Delete failed - ${error.message}`
  }
}
</script>

<style scoped>
div {
    text-align: center;
    padding: 20px;
}
input {
    display: block;
    margin: 5px auto;
    padding: 5px;
}
button {
    margin: 10px;
    padding: 10px 20px;
    background: red;
    color: white;
    border: none;
}
router-link {
    color: blue;
    text-decoration: none;
}
</style>
