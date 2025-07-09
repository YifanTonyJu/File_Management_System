<template>
  <div>
    <router-link to="/">← Back</router-link>
    <h1>Update File</h1>
    
    <input v-model="fileName" placeholder="Original file name (required)">
    <input v-model="filePath" placeholder="New file name (optional)">
    <input v-model="fileType" placeholder="New file type (required)">
    <button @click="updateFile">Update File</button>

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

const updateFile = async () => {
  try {
    if (!fileName.value) {
      message.value = 'Please enter the original file name to update'
      return
    }
    
    if (!fileType.value) {
      message.value = 'Please enter new file type'
      return
    }
    
    const response = await fetch('/api/files/' + fileName.value, {
      method: 'PUT',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({
        new_file_name: filePath.value || fileName.value,
        new_file_type: fileType.value
      })
    })
    
    if (!response.ok) {
      throw new Error('HTTP ' + response.status + ': ' + response.statusText)
    }
    
    message.value = 'File updated successfully!'
    fileName.value = filePath.value = fileType.value = ''
    fileSize.value = 0
    userId.value = ''
    
  }
  catch (error) {
    message.value = 'Update failed - ' + error.message
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
    background: blue;
    color: white;
    border: none;
}
router-link {
    color: blue;
    text-decoration: none;
}
</style>
