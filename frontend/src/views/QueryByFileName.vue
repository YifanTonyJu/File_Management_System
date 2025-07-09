<template>
  <div>
    <router-link to="/">← Back</router-link>
    <h1>Query File by Name</h1>
    
    <input v-model="fileName" placeholder="File name">
    <button @click="getFileByName">Search File</button>

    <p v-if="message">{{ message }}</p>

    <div v-if="file && file.file_name">
      <h3>File Details:</h3>
      <div class="file-item">
        <p><strong>ID:</strong> {{ file.id }}</p>
        <p><strong>Name:</strong> {{ file.file_name }}</p>
        <p><strong>Path:</strong> {{ file.file_path }}</p>
        <p><strong>Type:</strong> {{ file.file_type }}</p>
        <p><strong>Size:</strong> {{ file.file_size }} bytes</p>
        <p><strong>User ID:</strong> {{ file.user_id }}</p>
        <p><strong>Upload Time:</strong> {{ file.upload_time }}</p>
      </div>
    </div>
  </div>
</template>

<script setup>
import { ref } from 'vue'

const message = ref('')
const file = ref({})
const fileName = ref('')

const getFileByName = async () => {
  try {
    if (!fileName.value) {
      message.value = 'Please enter file name'
      return
    }
    
    const response = await fetch('/api/files/name/' + fileName.value)
    
    if (!response.ok) {
      throw new Error('Failed to get file')
    }
    
    const data = await response.json()
    
    if (data.found) {
      file.value = data.file
      message.value = 'File found: ' + fileName.value
    }
    else {
      file.value = {}
      message.value = 'File not found: ' + fileName.value
    }
    
  }
  catch (error) {
    message.value = 'Error: ' + error.message
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
    background: purple;
    color: white;
    border: none;
}

router-link {
    color: blue;
    text-decoration: none;
}

.file-item {
    border: 1px solid #ccc;
    margin: 10px auto;
    padding: 10px;
    max-width: 500px;
    text-align: left;
}

p {
    margin: 5px 0;
}
</style>
