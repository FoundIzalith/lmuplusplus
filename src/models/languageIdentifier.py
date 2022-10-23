from torch.utils.data import DataLoader, Dataset, random_split
import torchaudio
from ..bindings import lmu


class languageIdentifier:
    def __init__():
       
    def forward():

class audioData(Dataset):
    def __init__(self, filename, path, duration, sampleRate, channels, dataFrame):
        self.filename = filename
        self.path = path
        self.duration = duration
        self.sampleRate = sampleRate
        self.channels = channels
        self.dataFrame = dataFrame
        
    def __len__(self):
        return len(self.df)

    def __getitem__(self, id):
        audioFile = self.path + self.dataFrame.loc[id, 'relative_path']
        classID = self.dataFrame.loc[id, 'classID']
        file = AudioUtil.open(audioFile)
        #Ensure consistent data
        resampled = AudioUtil.resample(file, self.sampleRate)
        rechanneled = AudioUtil.rechannel(resample, self.channels)
        padded = AudioUtil.pad_trunc(rechanneled, self.duration)
        shifted = AudioUtil.time_shift(padded, 0.4)
        spectro = AudioUtil.spectro_gram(shifted, n_mels=64, n_fft=1024, hop_len=None)
        spectrogram = AudioUtil.spectro_augment(spectro, max_mask_pct=0.1, n_freq_masks=2, n_time_masks=2)

        return spectrogram, classID