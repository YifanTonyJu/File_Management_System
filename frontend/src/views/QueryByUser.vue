<template>
  <div>
    <router-link to="/">← Back</router-link>
    <h1>Query Files by User</h1>
    
    <input v-model="userId" placeholder="User ID">
    <button @click="getFilesByUser">Search Files</button>

    <p v-if="message">{{ message }}</p>

    <div v-if="files.length > 0">
      <h3>Files for User: {{ userId }}</h3>
      <div v-for="file in files" :key="file.file_name" class="file-item">
        <p><strong>Name:</strong> {{ file.file_name }}</p>
        <p><strong>Path:</strong> {{ file.file_path }}</p>
        <p><strong>Type:</strong> {{ file.file_type }}</p>
        <p><strong>Size:</strong> {{ file.file_size }} bytes</p>
        <p><strong>Upload Time:</strong> {{ file.upload_time }}</p>
        <hr>
      </div>
    </div>
  </div>
</template>

<script setup>
import { ref } from 'vue'

const message = ref('')
const files = ref([])
const userId = ref('')

const getFilesByUser = async () => {
  try {
    if (!userId.value) {
      message.value = 'Please enter User ID'
      return
    }
    
    const response = await fetch('/api/files/user/' + userId.value)
    
    if (!response.ok) {
      throw new Error('Failed to get files')
    }
    
    const data = await response.json()
    
    files.value = data.files
    message.value = 'Found ' + data.count + ' files for user ' + userId.value
    
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
    background: orange;
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

hr {
    margin: 10px 0;
}
</style>
