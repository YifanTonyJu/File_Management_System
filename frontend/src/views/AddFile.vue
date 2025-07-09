<template>
  <div>
    <router-link to="/">← Back</router-link>
    <h1>Add File</h1>
    
    <input v-model="fileName" placeholder="File name">
    <input v-model="filePath" placeholder="File path">
    <input v-model="fileType" placeholder="File type">
    <input v-model.number="fileSize" type="number" placeholder="File size">
    <input v-model="userId" placeholder="User ID">
    <button @click="addFile">Add File</button>

    <p v-if="message">{{ message }}</p>
  </div>
</template>

<script setup>
import { ref } from 'vue'

const message = ref('')
const fileName = ref('')
const filePath = ref('')
const fileType = ref('')
const fileSize = ref(0)
const userId = ref('')

const addFile = async () => {
  try {
    if (!fileName.value || !filePath.value || !fileType.value) {
      message.value = 'Please fill required fields: File name, File path, File type'
      return
    }
    
    const response = await fetch('/api/files', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({
        file_name: fileName.value,
        file_path: filePath.value,
        file_type: fileType.value,
        file_size: fileSize.value,
        user_id: userId.value
      })
    })
    
    if (!response.ok) {
      throw new Error(`HTTP ${response.status}: ${response.statusText}`)
    }
    
    message.value = 'File added successfully!'
    fileName.value = filePath.value = fileType.value = ''
    fileSize.value = 0
    userId.value = ''
    
  }
  catch (error) {
    message.value = `Add failed - ${error.message}`
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
    background: green;
    color: white;
    border: none;
}
router-link {
    color: blue;
    text-decoration: none;
}
</style>
